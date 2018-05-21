#include "group.h"

Group::Group()
{
    pthread_mutex_init(&mutex_um, NULL);
}

Group::~Group()
{
    pthread_mutex_destroy(&mutex_um);
}


bool Group::add_user(ll id, User* user)
{
    pthread_mutex_lock(&mutex_um);
    um[id] = user;
    pthread_mutex_unlock(&mutex_um);
    return true;
}

bool Group::remove_user(ll id)
{
    pthread_mutex_lock(&mutex_um);
    um.erase(id);
    pthread_mutex_unlock(&mutex_um);
    return true;
}