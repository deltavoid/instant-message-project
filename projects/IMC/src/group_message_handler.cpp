#include "group_message_handler.h"
#include "message.h"

GroupMessageHandler::GroupMessageHandler(GroupManager* gm)
    : RequestHandler(),  group_manager(gm)
{
}

GroupMessageHandler::~GroupMessageHandler()
{
}

void GroupMessageHandler::do_request(Request* req)
{
    ll user_id = req->param[1];
    ll message_id = req->param[2];

    Group* group = group_manager->get_group(user_id);

    pthread_mutex_lock(&group->mutex_um);
    std::map<ll, User*>::iterator it;
    for (it = group->um.begin(); it != group->um.end(); it++)
    {   
        User* user = it->second;
        pthread_mutex_lock(&user->mutex_mq);
        user->mq.push(new UserMessage(message_id));
        pthread_mutex_unlock(&user->mutex_mq);
    }
    pthread_mutex_unlock(&group->mutex_um);
}