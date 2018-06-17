#ifndef USER_H
#define USER_H
#include <vector>
#include <queue>
#include <pthread.h>
#include "message.h"


typedef long long ll;

class UserIterator;

class User
{public:
    std::queue<Message*> mq;
    pthread_mutex_t mutex_mq;

    User();
    virtual ~User();

    bool put_message(Message* message);
    //std::vector<Message*>* get_all_message();
    UserIterator* create_iterator();
};


class UserIterator
{public:
    User* user;

    UserIterator(User* user);
    virtual ~UserIterator();

    void first();
    void next();
    bool is_done();
    Message* current_item();


};

#endif
