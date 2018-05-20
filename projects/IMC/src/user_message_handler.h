#ifndef USER_MESSAGE_HANDLER_H
#define USER_MESSAGE_HANDLER_H
#include "request_handler.h"
#include "user_manager.h"


class UserMessageHandler : public RequestHandler
{public:
    UserManager* user_manager;

    UserMessageHandler(UserManager* um);
    ~UserMessageHandler();

    virtual void do_request(Request* req);

};


#endif