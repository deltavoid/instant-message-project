#ifndef REQUEST_CENTRE_H
#define REQUEST_CENTRE_H
#include "user_manager.h"
#include "request_handler.h"
#include <vector>


class RequestCentre
{public:
    UserManager* user_manager;
    std::vector<RequestHandler*> user_message_handlers;
    std::vector<RequestHandler*> get_handlers;
    
    RequestCentre(UserManager* um);
    ~RequestCentre();

    void add_request(Request* req);
    
};

#endif