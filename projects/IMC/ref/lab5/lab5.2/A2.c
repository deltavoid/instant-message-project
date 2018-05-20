#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <semaphore.h>

#define QUEUE_LEN 100
#define CONSUMER_NUM 4
#define PRODUCER_NUM 4
#define nloop 10

struct Node
{   int id;
    int author;
    int value;
};



struct Shared
{   struct Node queue[QUEUE_LEN];
    int f, p;
};



int main()
{
    int proc_flag = 0;
    int fd;
    struct Shared* s;
    sem_t mutex;//应该放到共享内存里，这样是错的
    pid_t pid;
    int status;
    int ret;
    int i;
    

    fd = open("share.txt", O_RDWR | O_CREAT, S_IRWXU);
    s = mmap(NULL, sizeof(struct Shared), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    close(fd);

    ret = sem_init(&mutex, 1, 1);
    if  (ret < 0)  {  perror("semaphore init error");  exit(-1);}
    
    for (i = 0; i < PRODUCER_NUM + CONSUMER_NUM; i++)
    {   if  (fork() == 0)
        {   proc_flag = i < PRODUCER_NUM? 1 : 2;
            break;
        }
    }

    if  (proc_flag == 1)
    {   //producer_proc();
        for (i = 0; i < nloop; i++)
        {
            sem_wait(&mutex);
            printf("producer pid:%d\n", getpid());
            sleep(0.1);
            sem_post(&mutex);
        }
        return 0;
    }
    else if  (proc_flag == 2)
    {   //consumer_proc();
        for (i = 0; i < nloop; i++)
        {
            sem_wait(&mutex);
            printf("consumer pid:%d\n", getpid());
            sleep(0.1);
            sem_post(&mutex);
        }
        return 0;
    }

    while (~(pid = wait(&status))) ;
    printf("parent\n");

    return 0;
}