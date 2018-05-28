#include "group_handler_manager.h"
#include <cstdlib>

GroupHandlerManager::GroupHandlerManager(GroupManager* gm)
    : gm(gm)
{
    const int num = 10;
    for (int i = 0; i < num; i++)
        ghs.push_back(new GroupHandler(gm));
}

GroupHandlerManager::~GroupHandlerManager()
{
    for (int i = 0; i < ghs.size(); i++)
        delete ghs[i];
}

void GroupHandlerManager::add_request(Request* req)
{
    int id = random() % ghs.size();
    ghs[id]->add_request(req);
}