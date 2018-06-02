#include "connection_handler.h"
#include <iostream>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>


static int sendfull(int fd, const char* msg, int len, int flags) {
    int remaining = len;
    const char* cur = msg;
    int sent;

    while (remaining > 0) {
        sent = send(fd, reinterpret_cast<const void*>(cur), remaining, flags);
        if (sent == -1) {
            std::cerr << "send() failed: " << strerror(errno) << std::endl;
            break;
        }
        cur += sent;
        remaining -= sent;
    }

    return (len - remaining);
}

static int recvfull(int fd, char* msg, int len, int flags) {
    int remaining = len;
    char* cur = msg;
    int recvd;

    while (remaining > 0) {
        recvd = recv(fd, reinterpret_cast<void*>(cur), remaining, flags);
        if ((recvd == -1) || (recvd == 0)) break;
        cur += recvd;
        remaining -= recvd;
    }

    return (len - remaining);
}

ConnectionHandler::ConnectionHandler(int sockfd, UserManager* um, GroupManager* gm, GroupHandlerManager* ghm)
    : sockfd(sockfd), um(um), gm(gm), ghm(ghm)
{
    std::cout << "sockfd: " << sockfd << std::endl;
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
        handle(request, sockfd);
    }

}

void ConnectionHandler::handle(Request* req, int sockfd)
{
    std::cout << "req: " << req->op << " " 
              << req->param[0] << " " << req->param[1] << " " << req->param[2] << std::endl;

    switch(req->op)
    {
        case REQ_ADD:       handle_add(req);            break;
        case REQ_REMOVE:    handle_remove(req);         break;
        case REQ_PUT_USER:  handle_user_message(req);   break;
        case REQ_PUT_GROUP: handle_group_message(req);  break;
        case REQ_GET:       handle_get(req, sockfd);    break;
        default:  break;
    }
}

void ConnectionHandler::handle_add(Request* req)
{
    ll uid = req->param[0];
    ll gid = req->param[1];
    Group* group = gm->get_group(gid);
    User* user = um->get_user(uid);
    group->add_user(uid, user);
    
    delete req;
}

void ConnectionHandler::handle_remove(Request* req)
{
    ll uid = req->param[0];
    ll gid = req->param[1];
    Group* group = gm->get_group(gid);
    group->remove_user(uid);

    delete req;
}

void ConnectionHandler::handle_user_message(Request* req)
{
    ll uid = req->param[1];
    ll message_id = req->param[2];
    Message* message = new Message(message_id, uid);
    
    User* user = um->get_user(uid);
    user->put_message(message);

    delete req;
}

void ConnectionHandler::handle_group_message(Request* req)
{
    ghm->add_request(req);
}

void ConnectionHandler::handle_get(Request* req, int sockfd)
{
    ll uid = req->param[0];
    User* user = um->get_user(uid);

    pthread_mutex_lock(&user->mutex_mq);
    ll num = user->mq.size();
    std::cout << "num: " << num << " message: " << std::endl;
    sendfull(sockfd, (char*)&num, sizeof(ll), 0);
    
    for (int i = 0; i < num; i++)
    {   Message* message = user->mq.front();
        user->mq.pop();
        std::cout << "message_id: " << message->message_id
                  << " user_id: " << message->user_id
                  << " group_id: " << message->group_id
                  << std::endl;
        sendfull(sockfd, (char*)message, sizeof(Message), 0);
        delete message;
    }
    std::cout << std::endl;
    pthread_mutex_unlock(&user->mutex_mq);

    delete req;
}