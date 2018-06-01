#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <unistd.h>
#include <pthread.h>

typedef long long ll;

const int ReaderNum = 4;
const int WriterNum = 4;
pthread_t readers[ReaderNum];
pthread_t writers[WriterNum];



struct State
{   int id;
    int content;
    int author;
};

int count;
State state;
pthread_rwlock_t lock_state;

const int Loop = 10;


void* read(void* arg)
{
    int id = *(int*)arg;

    for (int i = 0; i < Loop; i++)
    {
        pthread_rwlock_rdlock(&lock_state);
        printf("reader: %d state id: %d content: %d author: %d\n", id, state.id, state.content, state.author);
        pthread_rwlock_unlock(&lock_state);
        sleep(1);
    }

    return NULL;
}

void* write(void* arg)
{
    int id = *(int*)arg;

    for (int i = 0; i < Loop; i++)
    {
        pthread_rwlock_wrlock(&lock_state);
        state.id = ++count;
        state.content = random();
        state.author = id;
        pthread_rwlock_unlock(&lock_state);
        sleep(1);
    }

    return NULL;
}


int main()
{
    pthread_rwlockattr_t attr;
    pthread_rwlockattr_init(&attr);
    pthread_rwlockattr_setkind_np (&attr, PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP);
    //(void)pthread_rwlock_init(&rwlock, &attr);
    pthread_rwlock_init(&lock_state, &attr);

    for (int i = 0; i < ReaderNum; i++)
        pthread_create(&readers[i], NULL, read, (void*)new int(i));
    for (int i = 0; i < WriterNum; i++)
        pthread_create(&writers[i], NULL, write, (void*)new int(10 + i));

    void* res;
    for (int i = 0; i < ReaderNum; i++)
        pthread_join(readers[i], &res);
    for (int i = 0; i < WriterNum; i++)
        pthread_join(writers[i], &res);
    
    return 0;
}