#ifndef CONNECTION_HANDLER_MANAGER_H
#define CONNECTION_HANDLER_MANAGER_H
#include "connection_handler.h"

class ConnectionHandlerManager
{public:
    UserManager* um;
    GroupManager* gm;
    std::vector<ConnectionHandler*> chs;

    ConnectionHandlerManager(UserManager* um, GroupManager* gm);
    virtual ~ConnectionHandlerManager();

    void add_request(void* req);
};

#endif