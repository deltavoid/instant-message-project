#ifndef REQUEST_ENTRY_H
#define REQUEST_ENTRY_H

#include "request_centre.h"
#include "request_generator.h"
#include "pthread.h"


class RequestEntry
{public:
    RequestCentre* backend;
    std::vector<RequestGenerator*> generators;
    pthread_t tid;


    RequestEntry(RequestCentre* rc);
    ~RequestEntry();

    static void* thread_entry(void* arg);
    void run();
    
};

#endif