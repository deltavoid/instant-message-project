#include "connection_handler.h"
#include "request.h"
#include "helpers.h"
#include <iostream>
#include <unistd.h>



ConnectionHandler::ConnectionHandler(int sockfd, RequestHandlerManager* rhm)
    : sockfd(sockfd), rhm(rhm)
{
    pthread_create(&tid, NULL, thread_entry, (void*)this);
    pthread_detach(tid);
}

ConnectionHandler::~ConnectionHandler()
{
    pthread_cancel(tid);
}


void* ConnectionHandler::thread_entry(void* arg)
{
    ConnectionHandler* This = (ConnectionHandler*)arg;
    This->run();

    return NULL;
}

void ConnectionHandler::run()
{
    while (true)
    {
        //receive request 
        Request* request = new Request();
        int len = recvfull(sockfd, (char*)request, sizeof(Request), 0);
        if  (len == 0)  break;

        //handle request
        if  (request->op == REQ_GET)  request->param[1] = sockfd;
        rhm->add_request(request);
    }

    close(sockfd);
}