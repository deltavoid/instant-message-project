#ifndef USER_H
#define USER_H
#include "message.h"
#include <queue>
#include <pthread.h>


class User
{public:
    std::queue<Message*> mq;
    pthread_mutex_t mutex_mq;

    User();
    ~User();

};

#endif
