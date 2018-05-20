#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


struct Node
{   int id;
    int author;
    int value;
};

#define NUM_PRODUCERS 4
#define NUM_CONSUMERS 4
#define QUEUE_LEN 100
#define TOTAL_LEN 1000000

pthread_t thread_producers[NUM_PRODUCERS];
pthread_t thread_consumers[NUM_CONSUMERS];
int producer_args[NUM_PRODUCERS];
int consumer_args[NUM_CONSUMERS];

pthread_mutex_t mutex_queue;
struct Node Queue[QUEUE_LEN];
int f, p;



void* producer(void* argptr)
{
    int id;
    int i;
    int flag = 1;

    id = *(int*)argptr;

    while (flag)
    {
        pthread_mutex_lock(&mutex_queue);

        if  (p < TOTAL_LEN && p - f < QUEUE_LEN)
        {   int addr = p % QUEUE_LEN;
            Queue[addr].id = p;
            Queue[addr].author = id;
            Queue[addr].value = rand();
            p++;
        }

        if  (p >= TOTAL_LEN)  flag = 0;

        pthread_mutex_unlock(&mutex_queue);
        sleep(0.1);
    }

    pthread_exit(NULL);
}

void* consumer(void* argptr)
{
    int id;
    int i;
    int flag = 1;
    struct Node ans;

    id = *(int*)argptr;

    while (flag)
    {
        pthread_mutex_lock(&mutex_queue);

        if  (f < TOTAL_LEN && p - f > 0)
        {   int addr = f % QUEUE_LEN;
            ans = Queue[addr];
            printf("consumer_id:%d  product_id:%d  producer_id:%d value:%d\n",
                   id, ans.id, ans.author, ans.value);
            f++;
        }
                
        if  (f >= TOTAL_LEN)  flag = 0;

        pthread_mutex_unlock(&mutex_queue);
        sleep(0.1);
    }

    pthread_exit(NULL);
}


//线程管理
//*全局变量
//信号量

int main()
{
    int i;
    void* status;

    f = 0;  p = 1;

    pthread_mutex_init(&mutex_queue, NULL);

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

    pthread_mutex_destroy(&mutex_queue);

    pthread_exit(NULL);
}
