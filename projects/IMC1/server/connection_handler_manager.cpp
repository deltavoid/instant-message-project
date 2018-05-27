#include "connection_handler_manager.h"
#include <cstdlib>

ConnectionHandlerManager::ConnectionHandlerManager(UserManager* um, GroupManager* gm)
    : um(um), gm(gm)
{
    const int num = 4;
    for (int i = 0; i < num; i++)
        chs.push_back(new ConnectionHandler(um, gm));
}

ConnectionHandlerManager::~ConnectionHandlerManager()
{
    for (int i = 0; i < chs.size(); i++)
        delete chs[i];
}

void ConnectionHandlerManager::add_request(void* req)
{
    int id = random() % chs.size();
    chs[id]->add_request(req);
}