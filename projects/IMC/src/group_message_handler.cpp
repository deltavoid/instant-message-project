#include "group_message_handler.h"

GroupMessageHandler::GroupMessageHandler(UserManager* um, GroupManager* gm)
    : RequestHandler(), user_manager(um), group_manager(gm)
{
}

GroupMessageHandler::~GroupMessageHandler()
{
}

void GroupMessageHandler::do_request(Request* req)
{
    ll id = req->param[1];

    Group* group = group_manager->get_group(id);

    //
}