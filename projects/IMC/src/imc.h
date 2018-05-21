#ifndef IMC_H
#define IMC_H
#include "request_entry.h"
#include "request_centre.h"
#include "user_manager.h"
#include "group_manager.h"

class IMC
{public:
    RequestEntry* frontend;
    RequestCentre* backend;
    UserManager* user_manager;
    GroupManager* group_manager;


    IMC();
    virtual ~IMC();

};

#endif