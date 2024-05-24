#include "../include/externnum.h"
#include <iostream>
#include <thread>
#include "../include/setroom.h"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "%s\n", argv[0]);
        exit(0);
    }

    std::thread Setroom(setroom);
    Setroom.detach();

    int listenfd = Open_listenfd(atoi(argv[1]));

    int connfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;

    while (1)
    {
        {
            std::unique_lock<std::mutex> lock(mtxrun);
            if (!run)
                break;
        }
        clientlen = sizeof(struct sockaddr_storage);
        connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
        std::unique_lock<std::mutex> lock(mtxroom);
        clientdq.push_back(connfd);
        cond.notify_one();
    }
    Close(connfd);
    return 0;
}