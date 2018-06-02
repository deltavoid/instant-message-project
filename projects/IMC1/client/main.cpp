#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cstring>
#include <ctime>
#include <iostream>
#include <unistd.h>
#include "network_client.h"
#include "request.h"
#include "message.h"

const int user_num = 10;
const int group_num = 1;
NetworkClient* nc;



void gen_add()
{
    Request* req = new Request(REQ_ADD);
    req->param[0] = random() % user_num + 1;
    req->param[1] = random() % group_num + 1;
    nc->sendfull((char*)req, sizeof(Request), 0);
    delete req;
}

void gen_remove()
{
    Request* req = new Request(REQ_REMOVE);
    req->param[0] = random() % user_num + 1;
    req->param[1] = random() % group_num + 1;
    nc->sendfull((char*)req, sizeof(Request), 0);
    delete req;
}

void gen_user_message()
{
    Request* req = new Request(REQ_PUT_USER);
    req->param[0] = random() % user_num + 1;
    req->param[1] = random() % user_num + 1;
    req->param[2] = random();
    nc->sendfull((char*)req, sizeof(Request), 0);
    delete req;
}

void gen_group_message()
{
    Request* req = new Request(REQ_PUT_GROUP);
    req->param[0] = random() % user_num + 1;
    req->param[1] = random() % user_num + 1;
    req->param[2] = random();
    nc->sendfull((char*)req, sizeof(Request), 0);
    delete req;
}

void gen_get()
{
    Request* req = new Request(REQ_GET);
    req->param[0] = random() % user_num + 1;
    nc->sendfull((char*)req, sizeof(Request), 0);

    ll num = 0;
    nc->recvfull((char*)&num, sizeof(ll), 0);
    std::cout << "user: " << req->param[0]
              << " num: " << num
              << " message: " << std::endl;

    for (int i = 0; i < num; i++)
    {   Message* message = new Message();
        nc->recvfull((char*)message, sizeof(Message), 0);
        std::cout << "message_id: " << message->message_id
                  << " user_id: " << message->user_id
                  << " group_id: " << message->group_id
                  << std::endl;
        delete message;
    }
    std::cout << std::endl;
    delete req;
}

void gen_request(int type)
{
    switch(type)
    {
        case 0:  gen_add();  break;
        case 1:  //gen_remove();  break;
        case 2:  gen_user_message();  break;
        case 3:  gen_group_message();  break;
        case 4:  gen_get();  break;
        default:  break;
    }
}

int main(int argc, char *argv[])
{
    if  (argc < 3)
    {   fprintf(stderr, "usage: client <hostname> <request_num>\n");
        exit(1);
    }

    int num = 0;
    sscanf(argv[2], "%d", &num);
    
    srand(time(NULL));
    nc = new NetworkClient(argv[1], 3490);
    for (int i = 0; i < num; i++)
    {
        gen_request(/*random()*/i % 5);
    }
    delete nc;

    return 0;
}