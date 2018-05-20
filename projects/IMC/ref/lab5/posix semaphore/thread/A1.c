#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>


int number;
sem_t sem_id1, sem_id2;
pthread_t thread_id1, thread_id2;



void* thread_one_func(void* argptr)
{
    int i;

    for (i = 0; i < 10; i++)
    {
        sem_wait(&sem_id1);
        printf("thread_one have the semaphore\n");
        number++;
        printf("number:%d\n", number);
        sem_post(&sem_id2);
    }
}

void* thread_two_func(void* argptr)
{
    int i;

    for (i = 0; i < 10; i++)
    {
        sem_wait(&sem_id2);
        printf("thread_two have the semaphore\n");
        number--;
        printf("number:%d\n", number);
        sem_post(&sem_id1);
    }
}

int main()
{
    number = 1;
    sem_init(&sem_id1, 0, 1);
    sem_init(&sem_id2, 0, 0);

    pthread_create(&thread_id1, NULL, thread_one_func, NULL);
    pthread_create(&thread_id2, NULL, thread_two_func, NULL);

    pthread_join(thread_id1, NULL);
    pthread_join(thread_id2, NULL);

    sem_destroy(&sem_id1);
    sem_destroy(&sem_id2);

    printf("main\n");
    return 0;
}