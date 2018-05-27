#ifndef CONNECTION_HANDLER_MANAGER_H
#define CONNECTION_HANDLER_MANAGER_H
#include "connection_handler.h"

class ConnectionHandlerManager
{public:
    std::vector<ConnectionHandler*> chs;

    ConnectionHandlerManager();
    virtual ~ConnectionHandlerManager();

    void add_request(void* req);
};

#endif