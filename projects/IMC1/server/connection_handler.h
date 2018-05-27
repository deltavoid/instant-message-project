#ifndef CONNECTION_HANDLER_H
#define CONNECTION_HANDLER_H
#include "handler.h"
#include "request.h"
#include "user_manager.h"
#include "group_manager.h"

class ConnectionHandler : public Handler
{public:
    UserManager* um;
    GroupManager* gm;
    
    ConnectionHandler(UserManager* um, GroupManager* gm);
    virtual ~ConnectionHandler();

    virtual void do_request(void* req);

    void handle(Request* req, int sockfd);
    void handle_add(Request* req);
    void handle_remove(Request* req);
    void handle_user_message(Request* req);
    void handle_group_message(Request* req);
    void handle_get(Request* req, int sockfd);
};

#endif