#ifndef HANDLER_H
#define HANDLER_H
#include <queue>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

class Handler
{public:
    std::queue<void*> rq;
    pthread_mutex_t mutex_rq;
    sem_t sem_rq;
    pthread_t tid;

    Handler();
    virtual ~Handler();

    static void* thread_entry(void* arg);
    void run();
    virtual void do_request(void* req);

    bool add_request(void* req);
};

#endif