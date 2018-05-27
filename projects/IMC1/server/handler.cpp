#include "handler.h"
#include <iostream>


Handler::Handler()
{
    pthread_mutex_init(&mutex_rq, NULL);
    sem_init(&sem_rq, 0, 0);

    pthread_create(&tid, NULL, thread_entry, (void*)this);
    pthread_detach(tid);
}

Handler::~Handler()
{
    pthread_mutex_destroy(&mutex_rq);
    sem_destroy(&sem_rq);

    pthread_cancel(tid);
}


void* Handler::thread_entry(void* arg)
{
    Handler* This = (Handler*)arg;
    This->run();

    return NULL;
}

void Handler::run()
{
    while (true)
    {
        sem_wait(&sem_rq);
        pthread_mutex_lock(&mutex_rq);
        void* req = rq.front();
        rq.pop();
        pthread_mutex_unlock(&mutex_rq);

        do_request(req);  //it should delete the req
    }
}

void Handler::do_request(void* req)
{
    std::cout << "request at " << req << std::endl;
    delete req;
}

bool Handler::add_request(void* req)
{
    pthread_mutex_lock(&mutex_rq);
    //do queue overflow check
    rq.push(req);
    //std::cout << "queue size: " << rq.size() << std::endl;
    pthread_mutex_unlock(&mutex_rq);
    sem_post(&sem_rq);

    return true;
}
