#ifndef GROUP_USER_HANDLER_H
#define GROUP_USER_HANDLER_H
#include "request_handler.h"
#include "user_manager.h"
#include "group_manager.h"

class GroupUserHandler : public RequestHandler
{public:
    UserManager* user_manager;
    GroupManager* group_manager;

    GroupUserHandler(UserManager* um, GroupManager* gm);
    virtual ~GroupUserHandler();

    virtual void do_request(Request* req);
};

#endif