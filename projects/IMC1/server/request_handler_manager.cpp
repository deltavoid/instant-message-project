#include "request_handler_manager.h"
#include <cstdlib>

RequestHandlerManager::RequestHandlerManager(UserManager* um, GroupManager* gm, GroupHandlerManager* ghm)
    : um(um), gm(gm), ghm(ghm)
{
    const int num = 10;
    for (int i = 0; i < num; i++)
        rhs.push_back(new RequestHandler(um, gm, ghm));
}

RequestHandlerManager::~RequestHandlerManager()
{
    for (int i = 0; i < rhs.size(); i++)
        delete rhs[i];
}

void RequestHandlerManager::add_request(Request* req)
{
    int id = random() % rhs.size();
    rhs[id]->add_request(req);
}