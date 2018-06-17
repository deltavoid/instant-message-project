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

/*
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
}*/

UserIterator* User::create_iterator()
{
    return new UserIterator(this);
}


UserIterator::UserIterator(User* user) : user(user)
{
}

UserIterator::~UserIterator()
{
    pthread_mutex_unlock(&user->mutex_mq);
}

void UserIterator::first()
{
    pthread_mutex_lock(&user->mutex_mq);
}

void UserIterator::next()
{
    user->mq.pop();
}

bool UserIterator::is_done()
{
    return user->mq.empty();
}

Message* UserIterator::current_item()
{
    return user->mq.front();
}