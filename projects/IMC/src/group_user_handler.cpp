#include "group_user_handler.h"


GroupUserHandler::GroupUserHandler(UserManager* um, GroupManager* gm)
    : user_manager(um), group_manager(gm)
{
}

GroupUserHandler::~GroupUserHandler()
{
}

void GroupUserHandler::do_request(Request* req)
{
    if  (req->op == REQ_ADD)
    {
        ll user_id = req->param[0];
        ll group_id = req->param[1];
        User* user = user_manager->get_user(user_id);
        Group* group = group_manager->get_group(group_id);
        group->add_user(user_id, user);
    }
    else if  (req->op == REQ_REMOVE)
    {
        ll user_id = req->param[0];
        ll group_id = req->param[1];
        Group* group = group_manager->get_group(group_id);
        group->remove_user(user_id);
    }
}