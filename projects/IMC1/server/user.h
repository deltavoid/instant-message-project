#ifndef USER_H
#define USER_H
#include <vector>
#include <queue>
#include <pthread.h>


typedef long long ll;
//typedef ll message_t;


class User
{public:
    std::queue<ll> mq;
    pthread_mutex_t mutex_mq;

    User();
    virtual ~User();

    bool put_message(ll message_id);
    std::vector<ll>* get_all_message();
};

#endif
