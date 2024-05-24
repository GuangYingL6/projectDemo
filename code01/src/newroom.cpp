#include "../include/newroom.h"

void newroom(std::string sroom, int connfd)
{
    int n;
    char buf[MAXLINE];
    rio_t rio;
    Rio_readinitb(&rio, connfd);
    while ((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0)
    {
        std::unique_lock<std::mutex> lock(mtxrser);
        std::cout << "room[" << sroom << "](" << roomtree[sroom].first[connfd] << ") : " << buf << "\n";
        roomtree[sroom].second.push_back(buf);
        cond.notify_all();
    }
    std::unique_lock<std::mutex> lock(mtxrser);
    roomtree[sroom].first.erase(connfd);
    Close(connfd);
}

void workroom(std::string sroom)
{
    while (1)
    {
        std::unique_lock<std::mutex> lock(mtxrser);
        cond.wait(lock, [&sroom]()
                  { return !roomtree[sroom].second.empty(); });
        if (roomtree[sroom].first.empty())
        {
            roomtree.erase(sroom);
            break;
        }
        auto &msgs = roomtree[sroom].second;
        for (auto &[it, name] : roomtree[sroom].first)
        {
            while (!msgs.empty())
            {
                std::string msg = msgs.front();
                msgs.pop_front();
                msg = "[" + name + "] : " + msg;
                Rio_writen(it, const_cast<char *>(msg.c_str()), static_cast<int>(msg.size() + 1));
            }
        }
    }
}