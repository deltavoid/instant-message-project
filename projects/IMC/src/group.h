#ifndef GROUP_H
#define GROUP_H
#include "message.h"
#include <queue>


class UserInfo
{public:
    bool flag;
    

};

class Group
{public:
    std::queue<Message*> mq;
};

#endif