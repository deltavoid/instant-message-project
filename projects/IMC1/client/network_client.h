#ifndef NETWORK_CLIENT_H
#define NETWORK_CLIENT_H

class NetworkClient
{public:
    int sockfd;
    
    NetworkClient(const char* hostname, short port);
    virtual ~NetworkClient();

    int sendfull(const char* msg, int len, int flags);
    int recvfull(char* msg, int len, int flags);
};

#endif