#include "connection_entry.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/wait.h>

ConnectionEntry::ConnectionEntry(ConnectionHandlerManager* chm, short port, int backlog)
    : chm(chm)
{
    //int sockfd, new_fd; /* listen on sock_fd, new connection on new_fd */
    struct sockaddr_in my_addr; /* my address information */
    int sin_size;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        perror("socket");
        exit(1);
    }

    my_addr.sin_family = AF_INET; /* host byte order */
    my_addr.sin_port = htons(port); /* short, network byte order */
    my_addr.sin_addr.s_addr = INADDR_ANY; /* auto-fill with my IP */
    bzero(&(my_addr.sin_zero), sizeof(my_addr.sin_zero)); /* zero the rest of the struct */
    
    if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr))== -1) {
        perror("bind");
        exit(1);
    }

    if (listen(sockfd, backlog) == -1) {
        perror("listen");
        exit(1);
    }

    pthread_create(&tid, NULL, thread_entry, (void*)this);
    pthread_detach(tid);
}

ConnectionEntry::~ConnectionEntry()
{
    pthread_cancel(tid);
    close(sockfd);
}

void* ConnectionEntry::thread_entry(void* arg)
{
    ConnectionEntry* This = (ConnectionEntry*)arg;
    This->run();

    return NULL;
}

void ConnectionEntry::run()
{
    int new_fd;
    struct sockaddr_in their_addr; /* connector's address information */
    int sin_size = sizeof(struct sockaddr_in);

    while(true) { /* main accept() loop */

        if ((new_fd = accept(sockfd, (struct sockaddr *)&their_addr, (socklen_t*)&sin_size)) == -1) {
            perror("accept");
            continue;
        }

        printf("server: got connection from %s\n", inet_ntoa(their_addr.sin_addr));

        chm->add_handler(new_fd);
    }
}