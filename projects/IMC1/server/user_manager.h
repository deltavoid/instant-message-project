#ifndef USER_MANAGER_H
#define USER_MANAGER_H
#include "user.h"
#include <map>


class UserManager
{public:
    std::map<ll, User*> um;//it should use hash_map;
    //pthread_mutex_t mutex_um;  //it should use read-write lock
    pthread_rwlock_t lock_um;

    UserManager();
    virtual ~UserManager();

    User* get_user(ll id);

};



#endif