#include "connection_handler_manager.h"


ConnectionHandlerManager::ConnectionHandlerManager(RequestHandlerManager* rhm)
    : rhm(rhm)
{
}

ConnectionHandlerManager::~ConnectionHandlerManager()
{
}

void ConnectionHandlerManager::add_handler(int sockfd)
{
    chs.push_back(new ConnectionHandler(sockfd, rhm));
}