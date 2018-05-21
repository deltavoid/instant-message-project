#ifndef GROUP_MESSAGE_HANDLER_H
#define GROUP_MESSAGE_HANDLER_H
#include "request_handler.h"
#include "user_manager.h"
#include "group_manager.h"

class GroupMessageHandler : public RequestHandler
{public:
    UserManager* user_manager;
    GroupManager* group_manager;

    GroupMessageHandler(GroupManager* gm);
    ~GroupMessageHandler();

    virtual void do_request(Request* req);

};

#endif