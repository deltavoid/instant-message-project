#include "request_entry.h"
#include <cstdlib>
#include <iostream>


RequestEntry::RequestEntry(RequestCentre* rc)
{
    backend = rc;

    const int num = 10;
    for (int i = 0; i < num; i++)
        generators.push_back(new RequestGenerator(backend, 100));

    pthread_create(&tid, NULL, thread_entry, (void*)this);
    pthread_detach(tid);
}

RequestEntry::~RequestEntry()
{
    pthread_cancel(tid);
}

void* RequestEntry::thread_entry(void* arg)
{
    RequestEntry* This = (RequestEntry*)arg;
    This->run();

    return NULL;
}

void RequestEntry::run()
{
    ll num;
    while (std::cin >> num)
    {
        for (int i = 0; i < generators.size(); i++)
            generators[i]->rate = num;
    }

}