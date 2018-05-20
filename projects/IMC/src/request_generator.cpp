#include "request_generator.h"
#include <cstdlib>

RequestGenerator::RequestGenerator(RequestCentre* rc, ll rate)
    : backend(rc), rate(rate)
{

    pthread_create(&tid, NULL, thread_entry, (void*)this);
    pthread_detach(tid);
}

RequestGenerator::~RequestGenerator()
{
    pthread_cancel(tid);
}

void* RequestGenerator::thread_entry(void* arg)
{
    RequestGenerator* This = (RequestGenerator*)arg;
    This->run();

    return NULL;
}

void RequestGenerator::run()
{
    while (true)
    {
        for (int i = 0; i < rate; i++)
        {
            Request* req = new Request(0x01);
            req->param[0] = random();
            backend->add_request(req);
        }
        sleep(1);
    }

}