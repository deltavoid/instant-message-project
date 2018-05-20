#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <semaphore.h>

struct Shared
{   sem_t sem1, sem2;
    int cnt;
};


//sem放在共享内存里

int main(int argc, char** argv)
{
    int fd;
    char buf;
    struct Shared* s;
    int i;
    int count = 0, nloop = 10, zero = 0;
    int ret;
    //sem_t sem1, sem2;

    fd = open("log.txt", O_RDWR | O_CREAT, S_IRWXU);
    for (i = 0; i < sizeof(struct Shared); i++)  write(fd, &buf, sizeof(buf));
    s = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    close(fd);

    //ret = sem_init(&mutex, 1, 1);
    //if  (ret < 0)  {  perror("semaphtore initilization");  exit(0);}
    sem_init(&s->sem1, 1, 1);
    sem_init(&s->sem2, 1, 0);
    s->cnt = 0;

    if  (fork() == 0)
    {
        for (i = 0; i < nloop; i++)
        {   sem_wait(&s->sem1);
            printf("child: %d\n", s->cnt++);
            //printf("child\n");
            sleep(0.1);
            sem_post(&s->sem2);
        }
    }
    else 
    {
        for (i = 0; i < nloop; i++)
        {   sem_wait(&s->sem2);
            printf("parent: %d\n", s->cnt++);
            //printf("parent\n");
            sleep(0.1);
            sem_post(&s->sem1);
        }
    }


    //sem_destroy(&s->sem1);
    //sem_destroy(&s->sem2);

    exit(0);
}