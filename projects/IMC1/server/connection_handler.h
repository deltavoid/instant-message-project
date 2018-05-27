#ifndef CONNECTION_HANDLER_H
#define CONNECTION_HANDLER_H
#include "handler.h"

class ConnectionHandler : public Handler
{public:
    
    ConnectionHandler();
    virtual ~Connectionhandler();

    virtual void do_request(void* req);
};

#endif