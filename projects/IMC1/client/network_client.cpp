#include "network_client.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>

static int _sendfull(int fd, const char* msg, int len, int flags) {
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

static int _recvfull(int fd, char* msg, int len, int flags) {
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



NetworkClient::NetworkClient(const char* hostname, short port)
{
    struct hostent *he;
    struct sockaddr_in their_addr; /* connector's address information */


    if ((he = gethostbyname(hostname)) == NULL)
    { /* get the host info */
        herror("gethostbyname");
        exit(1);
    }
 
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        exit(1);
    }

    their_addr.sin_family = AF_INET; /* host byte order */
    their_addr.sin_port = htons(port); /* short, network byte order */
    their_addr.sin_addr = *((struct in_addr *)he->h_addr);
    bzero(&(their_addr.sin_zero), sizeof(their_addr.sin_zero)); /* zero the rest of the struct */
    
    if(connect(sockfd,(struct sockaddr *)&their_addr,sizeof(struct sockaddr)) == -1) {
        perror("connect");
        exit(1);
    }

}

NetworkClient::~NetworkClient()
{
    close(sockfd);
}

int NetworkClient::sendfull(const char* msg, int len, int flags)
{
    return _sendfull(sockfd, msg, len, flags);
}

int NetworkClient::recvfull(char* msg, int len, int flags)
{
    return _recvfull(sockfd, msg, len, flags);
}