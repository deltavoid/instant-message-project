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
    const int user_num = 1000;
    const int max_period = 10;

    while (true)
    {
        for (int i = 0; i < rate; i++)
        {
            ll op = random() % 2;
            Request* req;

            if  (op == 0)
            {   req = new Request(REQ_PUT_USER);
                req->param[0] = random() % user_num;
                req->param[1] = random() % user_num;
                req->param[2] = random();
                backend->add_user_message_request(req);
            }
            else if  (op == 1)
            {   req = new Request(REQ_GET);
                req->param[0] = random() % user_num;
                backend->add_get_request(req);
            }
            
        }
        sleep(random() % max_period);
    }

}