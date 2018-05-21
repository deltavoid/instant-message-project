#include "request_centre.h"
#include "user_message_handler.h"
#include "group_message_handler.h"
#include "get_handler.h"

RequestCentre::RequestCentre(UserManager* um, GroupManager* gm)
    : user_manager(um), group_manager(gm)
{
    const int num = 12;
    for (int i = 0; i < num; i++)
    {   user_message_handlers.push_back(new UserMessageHandler(user_manager));
        group_message_handlers.push_back(new GroupMessageHandler(group_manager));
        get_handlers.push_back(new GetHandler(user_manager));
    }
}

RequestCentre::~RequestCentre()
{
    for (int i = 0; i < user_message_handlers.size(); i++)
        delete user_message_handlers[i];
    for (int i = 0; i < get_handlers.size(); i++)
        delete get_handlers[i];
    for (int i = 0; i < get_handlers.size(); i++)
        delete group_message_handlers[i];
}

void RequestCentre::add_request(Request* req)
{
    switch(req->op)
    {
        case REQ_ADD:
        break;

        case REQ_REMOVE:
        break;

        case REQ_PUT_USER:
        {   ll id = req->param[1] % user_message_handlers.size();
            user_message_handlers[id]->add_request(req);
        }
        break;

        case REQ_PUT_GROUP:
        {   ll id = req->param[1] % group_message_handlers.size();
            group_message_handlers[id]->add_request(req);
        }
        break;

        case REQ_GET:
        {   ll id = req->param[0] % get_handlers.size();
            get_handlers[id]->add_request(req);
        }
        break;

        default:
        break;
    }
}
