#include "request_generator.h"
#include <cstdlib>
#include <iostream>

extern pthread_mutex_t mutex_cout;

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
    const int group_num = 1000;
    const int max_period = 10;
    const int socket_num = 100;

    while (true)
    {
        for (int i = 0; i < rate; i++)
        {
            ll op = random() % 3;
            Request* req;

            if  (op == 0)
            {   req = new Request(REQ_PUT_USER);
                req->param[0] = random() % user_num;
                req->param[1] = random() % user_num;
                req->param[2] = random();
            }
            else if  (op == 1)
            {   req = new Request(REQ_GET);
                req->param[0] = random() % user_num;
                req->param[1] = random() % socket_num;
            }
            else if  (op == 2)
            {   req = new Request(REQ_PUT_GROUP);
                req->param[0] = random() % user_num;
                req->param[1] = random() % group_num;
                req->param[2] = random();
            }
            
            pthread_mutex_lock(&mutex_cout);
            std::cout << "Generate request: " << req->op << " " 
                      << req->param[0] << " " << req->param[1] << " " << req->param[2] << std::endl;
            pthread_mutex_unlock(&mutex_cout);

            backend->add_request(req);
        }
        sleep(random() % max_period);
    }

}