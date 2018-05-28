#include "connection_handler_manager.h"
#include <cstdlib>

ConnectionHandlerManager::ConnectionHandlerManager(UserManager* um, GroupManager* gm, GroupHandlerManager* ghm)
    : um(um), gm(gm), ghm(ghm)
{
    const int num = 4;
    for (int i = 0; i < num; i++)
        chs.push_back(new ConnectionHandler(um, gm, ghm));
}

ConnectionHandlerManager::~ConnectionHandlerManager()
{
    for (int i = 0; i < chs.size(); i++)
        delete chs[i];
}

void ConnectionHandlerManager::add_request(int* req)
{
    int id = random() % chs.size();
    chs[id]->add_request(req);
}