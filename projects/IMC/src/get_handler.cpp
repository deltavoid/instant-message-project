#include "get_handler.h"
#include "user_manager.h"
#include <iostream>

extern pthread_mutex_t mutex_cout;


GetHandler::GetHandler(UserManager* um) 
    : RequestHandler(), user_manager(um)
{
}

GetHandler::~GetHandler()
{
}


void GetHandler::do_request(Request* req)
{
    ll user_id = req->param[0];

    User* user = user_manager->get_user(user_id);

    //此处应使用迭代器，由user提供
    pthread_mutex_lock(&mutex_cout);
    pthread_mutex_lock(&user->mutex_mq);
   

    std::cout << "user: " << req->param[0] << " socket: " << req->param[1] << " message: ";
    while (!user->mq.empty())
    {   Message* message = user->mq.front();
        user->mq.pop();
        std::cout << message->get_message() << " ";
        delete message;
    }
    std::cout << std::endl;

    
    pthread_mutex_unlock(&user->mutex_mq);
    pthread_mutex_unlock(&mutex_cout);

}