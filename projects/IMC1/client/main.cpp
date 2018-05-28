#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include "network_client.h"
#include "request.h"

const int user_num = 10;
const int group_num = 1;
NetworkClient* nc;



void gen_add()
{
    Request* req = new Request(REQ_ADD);
    req->param[0] = random() % user_num;
    req->param[1] = random() % group_num;
    nc->sendfull((char*)req, sizeof(Request), 0);
}

void gen_remove()
{
    Request* req = new Request(REQ_REMOVE);
    req->param[0] = random() % user_num;
    req->param[1] = random() % group_num;
    nc->sendfull((char*)req, sizeof(Request), 0);
}

void gen_user_message()
{
    Request* req = new Request(REQ_PUT_USER);
    req->param[0] = random() % user_num;
    req->param[1] = random() % user_num;
    req->param[2] = random();
    nc->sendfull((char*)req, sizeof(Request), 0);
}

void gen_group_message()
{
    Request* req = new Request(REQ_PUT_GROUP);
    req->param[0] = random() % user_num;
    req->param[1] = random() % user_num;
    req->param[2] = random();
    nc->sendfull((char*)req, sizeof(Request), 0);
}

void gen_get()
{
    Request* req = new Request(REQ_GET);
    req->param[0] = random() % user_num;
    nc->sendfull((char*)req, sizeof(Request), 0);

    ll num = 0;
    nc->recvfull((char*)&num, sizeof(ll), 0);
    std::cout << "user: " << req->param[0]
              << " num: " << num
              << " message: " << std::endl;
    for (int i = 0; i < num; i++)
    {   ll id = 0;
        nc->recvfull((char*)&id, sizeof(ll), 0);
        std::cout << id << " ";
    }
    std::cout << std::endl;
}

void gen_request(int type)
{
    switch(type)
    {
        case 0:  gen_add();  break;
        case 1:  //gen_remove();  break;
        case 2:  //gen_user_message();  break;
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
    
    for (int i = 0; i < num; i++)
    {
        nc = new NetworkClient(argv[1], 3490);
        gen_request(/*random()*/i % 5);
        delete nc;
    }

    return 0;
}