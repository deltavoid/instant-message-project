#ifndef GROUP_MANAGER_H
#define GROUP_MANAGER_H
#include "group.h"
#include <map>

class GroupManager
{public:
    std::map<ll, Group*> gm;
    pthread_mutex_t mutex_gm;

    GroupManager();
    ~GroupManager();

    Group* get_group(ll id);
};


#endif