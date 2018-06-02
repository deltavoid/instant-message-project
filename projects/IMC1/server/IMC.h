#ifndef IMC_H
#define IMC_H
#include "connection_entry.h"
#include "connection_handler_manager.h"
#include "request_handler_manager.h"
#include "group_handler_manager.h"
#include "group_manager.h"
#include "user_manager.h"



class IMC
{public:
    ConnectionEntry* ce;
    ConnectionHandlerManager* chm;
    RequestHandlerManager* rhm;
    GroupHandlerManager* ghm;
    GroupManager* gm;
    UserManager* um;

    IMC();
    virtual ~IMC();
    
};

#endif