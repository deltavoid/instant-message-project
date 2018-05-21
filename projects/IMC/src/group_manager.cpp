#include "group_manager.h"

GroupManager::GroupManager()
{
    pthread_mutex_init(&mutex_gm);
}

GroupManager::~GroupManager()
{
    pthread_mutex_destroy(&mutex_gm);
}


Group* GroupManager::get_group(ll id)
{
    pthread_mutex_lock(&mutex_gm);
    Group* group = gm[id];
    if  (group == NULL)
        group = gm[id] = new Group();
    pthread_mutex_unlock(&mutex_gm);

    return group;
}
