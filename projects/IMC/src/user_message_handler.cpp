#include "user_message_handler.h"


UserMessageHandler::UserMessageHandler(UserManager* um) 
    : RequestHandler(), user_manager(um)
{
}

UserMessageHandler::~UserMessageHandler()
{
}

void UserMessageHandler::do_request(Request* req)
{
    ll user_id = req->param[0];
    ll message_id = req->param[1];

    User* user = user_manager->get_user(user_id);
    
    pthread_mutex_lock(&user->mutex_mq);
    user->mq.push(new UserMessage(message_id));
    pthread_mutex_unlock(&user->mutex_mq);

}