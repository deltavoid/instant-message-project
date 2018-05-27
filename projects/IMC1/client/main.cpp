#include <cassert>
#include <cstring>
#include <iostream>
#include "network_client.h"

const int Len = 100;
char msg[Len];

int main(int argc, char *argv[])
{
    if  (argc != 2)
    {   fprintf(stderr, "usage: client hostname\n");
        exit(1);
    }

    NetworkClient* nc = new NetworkClient(argv[1], 3490);

    int len = nc->recvfull(msg, Len, 0);
    msg[len] = '\0';
    std::cout << msg << std::endl;

    delete nc;
    return 0;
}