#ifndef IMC_H
#define IMC_H
#include "request_entry.h"
#include "request_centre.h"
#include "user_manager.h"

class IMC
{public:
    RequestEntry* frontend;
    RequestCentre* backend;
    UserManager* user_manager;


    IMC();
    ~IMC();

};

#endif