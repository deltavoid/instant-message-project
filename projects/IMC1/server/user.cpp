#include "user.h"


User::User()
{
    pthread_mutex_init(&mutex_mq, NULL);
}

User::~User()
{
    //clean mq
    pthread_mutex_destroy(&mutex_mq);
}

bool User::put_message(ll message_id)
{
    pthread_mutex_lock(&mutex_mq);
    mq.push(message_id);
    pthread_mutex_unlock(&mutex_mq);
}

std::vector<ll>* User::get_all_message()
{
    std::vector<ll>* res = new std::vector<ll>();
    pthread_mutex_lock(&mutex_mq);
    while (!mq.empty())
    {   res->push_back(mq.front());
        mq.pop();
    }
    pthread_mutex_unlock(&mutex_mq);
    return res;
}