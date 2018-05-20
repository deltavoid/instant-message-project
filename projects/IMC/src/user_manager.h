#ifndef USER_MANAGER_H
#define USER_MANAGER_H
#include "user.h"
#include <map>


class UserManager
{public:
    std::map<ll, User*> user_map;//it should use hash_map;
    pthread_mutex_t mutex_um;  //it should use read-write lock

    UserManager();
    ~UserManager();

    User* get_user(ll id);

};



#endif