#include "request_handler.h"
#include <iostream>


RequestHandler::RequestHandler()
{
    pthread_mutex_init(&mutex_rq, NULL);
    sem_init(&sem_rq, 0, 0);

    pthread_create(&tid, NULL, thread_entry, (void*)this);
    pthread_detach(tid);
}

RequestHandler::~RequestHandler()
{
    pthread_mutex_destroy(&mutex_rq);
    sem_destroy(&sem_rq);

    pthread_cancel(tid);
}

void* RequestHandler::thread_entry(void* arg)
{
    RequestHandler* This = (RequestHandler*)arg;

    This->run();

    return NULL;
}

void RequestHandler::run()
{
    while (true)
    {
        sem_wait(&sem_rq);
        pthread_mutex_lock(&mutex_rq);
        Request* req = rq.front();
        rq.pop();
        pthread_mutex_unlock(&mutex_rq);

        do_request(req);
        
        delete req;
    }
}

void RequestHandler::do_request(Request* req)
{
    std::cout << "Request: " << req->op << " " << req->param[0] << " "
              << req->param[1] << " " << req->param[2] << std::endl;    
}

bool RequestHandler::add_request(Request* req)
{
    pthread_mutex_lock(&mutex_rq);
    //do queue overflow check
    rq.push(req);
    //std::cout << "queue size: " << rq.size() << std::endl;
    pthread_mutex_unlock(&mutex_rq);
    sem_post(&sem_rq);

    return true;
}

