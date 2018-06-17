#include "request_handler.h"
#include "helpers.h"
#include <iostream>
#include <algorithm>


RequestHandler::RequestHandler(UserManager* um, GroupManager* gm, GroupHandlerManager* ghm)
    : Handler(), um(um), gm(gm), ghm(ghm)
{
}

RequestHandler::~RequestHandler()
{
}

void RequestHandler::do_request(void* arg)
{
    Request* req = (Request*)arg;

    handle(req);

}

void RequestHandler::handle(Request* req)
{
    /*std::cout << "req: " << req->op << " " 
              << req->param[0] << " " << req->param[1] << " " << req->param[2] << std::endl;*/

    switch(req->op)
    {
        case REQ_ADD:       handle_add(req);            break;
        case REQ_REMOVE:    handle_remove(req);         break;
        case REQ_PUT_USER:  handle_user_message(req);   break;
        case REQ_PUT_GROUP: handle_group_message(req);  break;
        case REQ_GET:       handle_get(req);    break;
        default:  break;
    }
}

void RequestHandler::handle_add(Request* req)
{
    ll uid = req->param[0];
    ll gid = req->param[1];
    Group* group = gm->get_group(gid);
    User* user = um->get_user(uid);
    group->add_user(uid, user);
    
    delete req;
}

void RequestHandler::handle_remove(Request* req)
{
    ll uid = req->param[0];
    ll gid = req->param[1];
    Group* group = gm->get_group(gid);
    group->remove_user(uid);

    delete req;
}

void RequestHandler::handle_user_message(Request* req)
{
    ll uid = req->param[1];
    ll message_id = req->param[2];
    Message* message = new Message(message_id, uid);
    
    User* user = um->get_user(uid);
    user->put_message(message);

    delete req;
}

void RequestHandler::handle_group_message(Request* req)
{
    ghm->add_request(req);
}


void RequestHandler::handle_get(Request* req)
{
    ll uid = req->param[0];
    int sockfd = (int)req->param[1];
    User* user = um->get_user(uid);

    char* cur = buf;
    cur += sizeof(ll);
    UserIterator* it = user->create_iterator();
    ll num = 0;

    for (it->first(); !it->is_done() && num <= MaxRequests; it->next(), num++)
    {
        Message* message = it->current_item();
        memcpy(cur, (char*)message, sizeof(Message));
        cur += sizeof(Message);
        delete message;
    }
    delete it;

    (*(ll*)buf) = num;
    sendfull(sockfd, buf, cur - buf, 0);

    delete req;
}
