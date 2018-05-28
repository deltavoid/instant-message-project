#ifndef GROUP_HANDLER_MANAGER_H
#define GROUP_HANDLER_MANAGER_H
#include "group_handler.h"
#include "group_manager.h"
#include "request.h"
#include <vector>

class GroupHandlerManager
{public:
    std::vector<GroupHandler*> ghs;
    GroupManager* gm;

    GroupHandlerManager(GroupManager* gm);
    ~GroupHandlerManager();

    void add_request(Request* req);

};

#endif