#include "user_manager.h"

UserManager::UserManager()
{
    //pthread_mutex_init(&mutex_um, NULL);
    pthread_rwlock_init(&lock_um, NULL);
}

UserManager::~UserManager()
{
    //clean all users in um
    //pthread_mutex_destroy(&mutex_um);
    pthread_rwlock_destroy(&lock_um);
}

User* UserManager::get_user(ll id)
{
    /*pthread_mutex_lock(&mutex_um);
    User* user = um[id];
    if  (user == NULL)
        user = um[id] = new User();
    pthread_mutex_unlock(&mutex_um);*/

    pthread_rwlock_rdlock(&lock_um);
    std::map<ll, User*>::iterator it = um.find(id);
    pthread_rwlock_unlock(&lock_um);
    if  (it != um.end())  return it->second;

    pthread_rwlock_wrlock(&lock_um);
    User* user = um[id] = new User();
    pthread_rwlock_unlock(&lock_um);

    return user;
}