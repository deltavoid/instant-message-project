#ifndef IMC_H
#define IMC_H
#include "connection_entry.h"
#include "connection_handler_manager.h"


class IMC
{public:
    ConnectionEntry* ce;
    ConnectionHandlerManager* chm;

    IMC();
    virtual ~IMC();
    
};

#endif