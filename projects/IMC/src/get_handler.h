#ifndef GET_HANDLER_H
#define GET_HANDLER_H
#include "request_handler.h"
#include "user_manager.h"

class GetHandler : public RequestHandler
{public:
    UserManager* user_manager;

    GetHandler(UserManager* um);
    ~GetHandler();

    virtual void do_request(Request* req);

};


#endif
