#ifndef REQUEST_HANDLER_H
#define REQUEST_HANDLER_H
#include "handler.h"
#include "request.h"
#include "user_manager.h"
#include "group_manager.h"
#include "group_handler_manager.h"

class RequestHandler : public Handler
{public:
    UserManager* um;
    GroupManager* gm;
    GroupHandlerManager* ghm;

    static const int BufSize = 65536;
    char buf[BufSize];
    
    RequestHandler(UserManager* um, GroupManager* gm, GroupHandlerManager* ghm);
    virtual ~RequestHandler();

    virtual void do_request(void* arg);

    void handle(Request* req);
    void handle_add(Request* req);
    void handle_remove(Request* req);
    void handle_user_message(Request* req);
    void handle_group_message(Request* req);
    void handle_get(Request* req);
};

#endif