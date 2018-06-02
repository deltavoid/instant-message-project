#ifndef CONNECTION_HANDLER_MANAGER_H
#define CONNECTION_HANDLER_MANAGER_H
#include "connection_handler.h"
#include "request_handler_manager.h"
#include <vector>

class ConnectionHandlerManager
{public:
    RequestHandlerManager* rhm;
    std::vector<ConnectionHandler*> chs;

    ConnectionHandlerManager(RequestHandlerManager* rhm);
    virtual ~ConnectionHandlerManager();

    void add_handler(int sockfd);
    
};


#endif