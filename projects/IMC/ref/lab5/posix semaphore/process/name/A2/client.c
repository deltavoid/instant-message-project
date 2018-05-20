#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <semaphore.h>


char SEM_NAME1[] = "vik1";
char SEM_NAME2[] = "vik2";

int main()
{
    sem_t* mutex1;
    sem_t* mutex2;
    int i;
    

    mutex1 = sem_open(SEM_NAME1, O_CREAT, 0644, 1);
    mutex2 = sem_open(SEM_NAME2, O_CREAT, 0644, 0);
    if  (mutex1 == SEM_FAILED || mutex2 == SEM_FAILED)
    {   perror("unable to create semaphore");
        sem_unlink(SEM_NAME1);
        sem_unlink(SEM_NAME2);
        exit(-1);
    }

    printf("client prepare\n");

    for (i = 0; i < 10; i++)
    {
        sem_wait(mutex2);
        printf("client\n");
        sleep(1);
        sem_post(mutex1);
    }

    sleep(1);

    sem_close(mutex1);
    //sem_unlink(SEM_NAME1);
    sem_close(mutex2);
    //sem_unlink(SEM_NAME2);

    exit(0);
}