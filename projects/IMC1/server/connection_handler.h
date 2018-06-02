#ifndef CONNECTION_HANDLER_H
#define CONNECTION_HANDLER_H
#include "request_handler_manager.h"
#include "pthread.h"


class ConnectionHandler
{public:
    RequestHandlerManager* rhm;
    pthread_t tid;
    int sockfd;

    ConnectionHandler(int sockfd, RequestHandlerManager* rhm);
    virtual ~ConnectionHandler();

    static void* thread_entry(void* arg);
    void run();
    
};

#endif