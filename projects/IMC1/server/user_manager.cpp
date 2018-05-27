#include "user_manager.h"

UserManager::UserManager()
{
    pthread_mutex_init(&mutex_um, NULL);
}

UserManager::~UserManager()
{
    //clean all users in user_map
    pthread_mutex_destroy(&mutex_um);
}

User* UserManager::get_user(ll id)
{
    pthread_mutex_lock(&mutex_um);
    User* user = user_map[id];
    if  (user == NULL)
        user = user_map[id] = new User();
    pthread_mutex_unlock(&mutex_um);

    return user;
}