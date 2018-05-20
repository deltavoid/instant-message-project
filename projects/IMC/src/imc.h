#ifndef IMC_H
#define IMC_H
#include "request_entry.h"
#include "request_centre.h"

class IMC
{public:
    RequestEntry* frontend;
    RequestCentre* backend;

    IMC();
    ~IMC();

};

#endif