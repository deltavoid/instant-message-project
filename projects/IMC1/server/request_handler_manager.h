#ifndef REQUEST_HANDLER_MANAGER_H
#define REQUEST_HANDLER_MANAGER_H
#include "request_handler.h"

class RequestHandlerManager
{public:
    UserManager* um;
    GroupManager* gm;
    GroupHandlerManager* ghm;
    std::vector<RequestHandler*> rhs;

    RequestHandlerManager(UserManager* um, GroupManager* gm, GroupHandlerManager* ghm);
    virtual ~RequestHandlerManager();

    void add_request(Request* req);
};

#endif