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

bool User::put_message(Message* message)
{
    pthread_mutex_lock(&mutex_mq);
    mq.push(message);
    pthread_mutex_unlock(&mutex_mq);
}

std::vector<Message*>* User::get_all_message()
{
    std::vector<Message*>* res = new std::vector<Message*>();
    pthread_mutex_lock(&mutex_mq);
    while (!mq.empty())
    {   res->push_back(mq.front());
        mq.pop();
    }
    pthread_mutex_unlock(&mutex_mq);
    return res;
}