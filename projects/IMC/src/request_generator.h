#ifndef REQUEST_GENERATOR_H
#define REQUEST_GENERATOR_H
#include "request_centre.h"


class RequestGenerator
{public:
    RequestCentre* backend;
    pthread_t tid;
    ll rate;

    RequestGenerator(RequestCentre* rc, ll rate);
    virtual ~RequestGenerator();

    static void* thread_entry(void* arg);
    void run();

    
};

#endif