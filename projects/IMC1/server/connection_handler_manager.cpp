#include "connection_handler_manager.h"
#include <cstdlib>

ConnectionHandlerManager::ConnectionHandlerManager(UserManager* um, GroupManager* gm, GroupHandlerManager* ghm)
    : um(um), gm(gm), ghm(ghm)
{
}

ConnectionHandlerManager::~ConnectionHandlerManager()
{
    for (int i = 0; i < chs.size(); i++)
        delete chs[i];
}

void ConnectionHandlerManager::add_handler(int sockfd)
{
    chs.push_back(new ConnectionHandler(sockfd, um, gm, ghm));
}