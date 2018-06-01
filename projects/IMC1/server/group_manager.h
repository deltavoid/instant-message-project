#ifndef GROUP_MANAGER_H
#define GROUP_MANAGER_H
#include "group.h"
#include <map>
#include "pthread.h"

class GroupManager
{public:
    std::map<ll, Group*> gm;
    //pthread_mutex_t mutex_gm;
    pthread_rwlock_t lock_gm;

    GroupManager();
    virtual ~GroupManager();

    Group* get_group(ll id);
};


#endif