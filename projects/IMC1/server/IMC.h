#ifndef IMC_H
#define IMC_H
#include "connection_entry.h"
#include "connection_handler_manager.h"
#include "user_manager.h"
#include "group_manager.h"


class IMC
{public:
    UserManager* um;
    GroupManager* gm;
    ConnectionEntry* ce;
    ConnectionHandlerManager* chm;

    IMC();
    virtual ~IMC();
    
};

#endif