#include "group_manager.h"

GroupManager::GroupManager()
{
    //pthread_mutex_init(&mutex_gm, NULL);
    pthread_rwlock_init(&lock_gm, NULL);
}

GroupManager::~GroupManager()
{
    //pthread_mutex_destroy(&mutex_gm);
    pthread_rwlock_destroy(&lock_gm);
}


Group* GroupManager::get_group(ll id)
{
    /*pthread_mutex_lock(&mutex_gm);
    Group* group = gm[id];
    if  (group == NULL)
        group = gm[id] = new Group();
    pthread_mutex_unlock(&mutex_gm);*/

    pthread_rwlock_rdlock(&lock_gm);
    std::map<ll, Group*>::iterator it = gm.find(id);
    pthread_rwlock_unlock(&lock_gm);
    if  (it != gm.end()) return it->second;

    pthread_rwlock_wrlock(&lock_gm);
    Group* group = gm[id] = new Group();
    pthread_rwlock_unlock(&lock_gm);

    return group;
}
