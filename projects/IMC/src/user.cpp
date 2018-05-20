#include "user.h"


User::User()
{
    pthread_mutex_init(&mutex_mq, NULL);
}

User::~User()
{
    //clean mq
    pthread_mutex_destroy(&mutex_mq);
}