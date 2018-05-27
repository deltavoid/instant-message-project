#include "connection_handler.h"
#include <iostream>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>


static int sendfull(int fd, const char* msg, int len, int flags) {
    int remaining = len;
    const char* cur = msg;
    int sent;

    while (remaining > 0) {
        sent = send(fd, reinterpret_cast<const void*>(cur), remaining, flags);
        if (sent == -1) {
            std::cerr << "send() failed: " << strerror(errno) << std::endl;
            break;
        }
        cur += sent;
        remaining -= sent;
    }

    return (len - remaining);
}

static int recvfull(int fd, char* msg, int len, int flags) {
    int remaining = len;
    char* cur = msg;
    int recvd;

    while (remaining > 0) {
        recvd = recv(fd, reinterpret_cast<void*>(cur), remaining, flags);
        if ((recvd == -1) || (recvd == 0)) break;
        cur += recvd;
        remaining -= recvd;
    }

    return (len - remaining);
}

ConnectionHandler::ConnectionHandler()
{
}

ConnectionHandler::~ConnectionHandler()
{
}

void ConnectionHandler::do_request(void* req)
{
    int sockfd = (*(int*)req);
    std::cout << "sockfd is " << sockfd << std::endl;

    int len = sendfull(sockfd, "Hello, world!\n", 14, 0);

    close(sockfd);
    delete (int*)req;
}