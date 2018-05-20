#include "request_centre.h"
#include "user_message_handler.h"
#include "get_handler.h"

RequestCentre::RequestCentre(UserManager* um)
    : user_manager(um)
{
    const int num = 12;
    for (int i = 0; i < num; i++)
    {   user_message_handlers.push_back(new UserMessageHandler(user_manager));
        get_handlers.push_back(new GetHandler(user_manager));
    }
}

RequestCentre::~RequestCentre()
{
    for (int i = 0; i < user_message_handlers.size(); i++)
        delete user_message_handlers[i];
    for (int i = 0; i < get_handlers.size(); i++)
        delete get_handlers[i];
}

void RequestCentre::add_user_message_request(Request* req)
{
    int id  = req->param[0] % user_message_handlers.size();
    req->param[1] = id;
    user_message_handlers[id]->add_request(req);
}

void RequestCentre::add_get_request(Request* req)
{
    int id  = req->param[0] % get_handlers.size();
    req->param[1] = id;
    get_handlers[id]->add_request(req);
}