#ifndef CONNECTION_HANDLER_H
#define CONNECTION_HANDLER_H
#include "handler.h"
#include "request.h"
#include "user_manager.h"
#include "group_manager.h"
#include "group_handler_manager.h"
#include "pthread.h"

class ConnectionHandler 
{public:
    UserManager* um;
    GroupManager* gm;
    GroupHandlerManager* ghm;
    int sockfd;
    pthread_t tid;
    
    ConnectionHandler(int sockfd, UserManager* um, GroupManager* gm, GroupHandlerManager* ghm);
    virtual ~ConnectionHandler();

    static void* thread_entry(void* arg);
    void run();

    void handle(Request* req, int sockfd);
    void handle_add(Request* req);
    void handle_remove(Request* req);
    void handle_user_message(Request* req);
    void handle_group_message(Request* req);
    void handle_get(Request* req, int sockfd);
};

#endif