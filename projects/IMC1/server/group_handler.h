#ifndef GROUP_HANDLER_H
#define GROUP_HANDLER_H
#include "handler.h"
#include "group_manager.h"

class GroupHandler : public Handler
{public:
    GroupManager* gm;

    GroupHandler(GroupManager* gm);
    virtual ~GroupHandler();

    virtual void do_request(void* arg);

};


#endif