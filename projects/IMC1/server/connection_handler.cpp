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

ConnectionHandler::ConnectionHandler(UserManager* um, GroupManager* gm)
    : Handler(), um(um), gm(gm)
{
}

ConnectionHandler::~ConnectionHandler()
{
}

void ConnectionHandler::do_request(void* req)
{
    int sockfd = (*(int*)req);
    std::cout << "sockfd is " << sockfd << std::endl;

    //receive request 
    Request* request = new Request();
    int len = recvfull(sockfd, (char*)request, sizeof(Request), 0);
    
    //handle request
    handle(request, sockfd);

    close(sockfd);
    delete (int*)req;
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
}

void ConnectionHandler::handle_remove(Request* req)
{
    ll uid = req->param[0];
    ll gid = req->param[1];
    Group* group = gm->get_group(gid);
    group->remove_user(uid);
}

void ConnectionHandler::handle_user_message(Request* req)
{
    ll uid = req->param[1];
    ll message_id = req->param[2];
    User* user = um->get_user(uid);
    user->put_message(message_id);
}

void ConnectionHandler::handle_group_message(Request* req)
{
}

void ConnectionHandler::handle_get(Request* req, int sockfd)
{
    ll uid = req->param[0];
    User* user = um->get_user(uid);

    pthread_mutex_lock(&user->mutex_mq);
    ll num = user->mq.size();
    std::cout << "num: " << num << " message: ";
    sendfull(sockfd, (char*)&num, sizeof(ll), 0);
    for (int i = 0; i < num; i++)
    {   ll id = user->mq.front();
        user->mq.pop();
        std::cout << id << " ";
        sendfull(sockfd, (char*)&id, sizeof(ll), 0);
    }
    std::cout << std::endl;
    pthread_mutex_unlock(&user->mutex_mq);
}