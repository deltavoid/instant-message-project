#ifndef USER_H
#define USER_H
#include <vector>
#include <queue>
#include <pthread.h>
#include "message.h"


typedef long long ll;



class User
{public:
    std::queue<Message*> mq;
    pthread_mutex_t mutex_mq;

    User();
    virtual ~User();

    bool put_message(Message* message);
    std::vector<Message*>* get_all_message();
};

#endif
