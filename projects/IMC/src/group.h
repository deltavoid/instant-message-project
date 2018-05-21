#ifndef GROUP_H
#define GROUP_H
#include "message.h"
#include "user.h"
#include <queue>
#include <map>


class Group
{public:
    std::map<ll, User*> um;
    pthread_mutex_t mutex_um;  //it should use read-write lock;

    Group();
    virtual ~Group();

    bool add_user(ll id, User* user);
    bool remove_user(ll id);
    
};

#endif