#include "request_centre.h"

RequestCentre::RequestCentre()
{
    const int num = 6;
    for (int i = 0; i < num; i++)
    {   handlers.push_back(new RequestHandler());
    }
}

RequestCentre::~RequestCentre()
{
    for (int i = 0; i < handlers.size(); i++)
        delete handlers[i];
}

void RequestCentre::add_request(Request* req)
{
    int id  = req->param[0] % handlers.size();
    req->param[1] = id;
    handlers[id]->add_request(req);
}