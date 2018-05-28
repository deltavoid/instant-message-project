#include "group_handler.h"
#include "request.h"


GroupHandler::GroupHandler(GroupManager* gm)
    : Handler(), gm(gm)
{
}

GroupHandler::~GroupHandler()
{
}

void GroupHandler::do_request(void* arg)
{
    Request* req = (Request*)arg;
    ll gid = req->param[1];
    ll message_id = req->param[2];

    Group* group = gm->get_group(gid);
    pthread_mutex_lock(&group->mutex_um);
    std::map<ll, User*>::iterator it;
    for (it = group->um.begin(); it != group->um.end(); it++)
    {   User* user = it->second;
        user->put_message(message_id);
    }
    pthread_mutex_unlock(&group->mutex_um);

    delete req;
}