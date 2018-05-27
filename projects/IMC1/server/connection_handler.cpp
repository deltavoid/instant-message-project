#include "connection_handler.h"
#include <iostream>

ConnectionHandler::ConnectionHandler()
{
}

ConnectionHandler::~ConnectionHandler()
{
}

void ConnectionHandler::do_request(void* req)
{
    int socket = (int)(*(long*)req);

    std::cout << "socket is " << socket << std::endl;


}