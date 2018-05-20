#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>


struct Node
{   int id;
    int author;
    int value;
};

#define NUM_PRODUCERS 4
#define NUM_CONSUMERS 4
#define QUEUE_LEN 100
#define TOTAL_LEN 100

pthread_t thread_producers[NUM_PRODUCERS];
pthread_t thread_consumers[NUM_CONSUMERS];
int producer_args[NUM_PRODUCERS];
int consumer_args[NUM_CONSUMERS];

sem_t mutex, empty, full;
struct Node Queue[QUEUE_LEN];
int f, p;



void* producer(void* argptr)
{
    int id;
    int i;
    int flag = 1;
    struct Node tmp;
    int addr;

    id = *(int*)argptr;

    while (flag)
    {
        tmp.author = id;
        tmp.value = rand();

        sem_wait(&empty);
        sem_wait(&mutex);

        addr = p % QUEUE_LEN;
        tmp.id = p;
        Queue[addr] = tmp;
        p++;
        if  (p > TOTAL_LEN)  flag = 0;

        sem_post(&mutex);
        sem_post(&full);
        sleep(0.1);
    }

    printf("producer %d exit\n", id);
    pthread_exit(NULL);
}

void* consumer(void* argptr)
{
    int id;
    int i;
    int flag = 1;
    struct Node ans;
    int addr;

    id = *(int*)argptr;

    while (flag)
    {
        sem_wait(&full);
        sem_wait(&mutex);

        addr = f % QUEUE_LEN;
        ans = Queue[addr];
        f++;
        if  (f > TOTAL_LEN)  flag = 0;

        sem_post(&mutex);
        sem_post(&empty);

        printf("consumer_id:%d  product_id:%d  producer_id:%d value:%d\n",
                id, ans.id, ans.author, ans.value);
        
        sleep(0.1);
    }

    printf("consumer %d exit\n", id);
    pthread_exit(NULL);
}


//线程管理
//*全局变量
//信号量

int main()
{
    int i;
    void* status;

    f = 0;  p = 0;//initally it has NONE item.

    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, QUEUE_LEN);
    sem_init(&full, 0, 0);//empty,full must match with f,p

    for (i = 0; i < NUM_PRODUCERS; i++)
    {   producer_args[i] = i;
        pthread_create(&thread_producers[i], NULL, producer, (void*)&producer_args[i]);
    }

    for (i = 0; i < NUM_CONSUMERS; i++)
    {   consumer_args[i] = i;
        pthread_create(&thread_consumers[i], NULL, consumer, (void*)&consumer_args[i]);
    }


    for (i = 0; i < NUM_PRODUCERS; i++)
        pthread_join(thread_producers[i], &status);
    for (i = 0; i < NUM_CONSUMERS; i++)
        pthread_join(thread_consumers[i], &status);

    sem_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    printf("f:%d p:%d\n", f, p);

    pthread_exit(NULL);
}
