#ifndef CONNECTION_ENTRY_H
#define CONNECTION_ENTRY_H
//#include "connection_handler_manager.h"
#include <pthread.h>

class ConnectionEntry
{public:
    //ConnectionHandlerManager* chm;
    pthread_t tid;
    //socket info
    short MYPORT;
    int BACKLOG;
    int sockfd;
    
    

    ConnectionEntry(/*ConnectionHandlerManager* chm,*/ short port = 3490, int backlog = 10);
    virtual ~ConnectionEntry();

    static void* thread_entry(void* arg);
    void run();


};

#endif