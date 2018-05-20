#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <semaphore.h>



//错误，没有放到共享内存里

int main(int argc, char** argv)
{
    int fd;
    int i;
    int count = 0, nloop = 10, zero = 0;
    int* ptr;
    int ret;
    sem_t mutex;

    fd = open("log.txt", O_RDWR | O_CREAT, S_IRWXU);
    write(fd, &zero, sizeof(int));
    ptr = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    close(fd);

    ret = sem_init(&mutex, 1, 1);
    if  (ret < 0)  {  perror("semaphtore initilization");  exit(0);}

    if  (fork() == 0)
    {
        for (i = 0; i < nloop; i++)
        {   sem_wait(&mutex);
            printf("child: %d\n", (*ptr)++);
            sleep(0.1);
            sem_post(&mutex);
        }
    }
    else 
    {
        for (i = 0; i < nloop; i++)
        {   sem_wait(&mutex);
            printf("parent: %d\n", (*ptr)++);
            sleep(0.1);
            sem_post(&mutex);
        }
    }

    ret = sem_destroy(&mutex);
    if  (ret < 0)  {  perror("semaphtore destroy error");  exit(0);}


    exit(0);
}