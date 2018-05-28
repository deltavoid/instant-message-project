#ifndef CONNECTION_HANDLER_MANAGER_H
#define CONNECTION_HANDLER_MANAGER_H
#include "connection_handler.h"

class ConnectionHandlerManager
{public:
    UserManager* um;
    GroupManager* gm;
    GroupHandlerManager* ghm;
    std::vector<ConnectionHandler*> chs;

    ConnectionHandlerManager(UserManager* um, GroupManager* gm, GroupHandlerManager* ghm);
    virtual ~ConnectionHandlerManager();

    void add_request(int* req);
};

#endif