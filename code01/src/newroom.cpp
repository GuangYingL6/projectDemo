#include "../include/newroom.h"

void newroom(std::string sroom, int connfd)
{
    {
        std::string s1 = sroom + " " + std::to_string(connfd) + " newroom start!\n";
        Fputs(s1.c_str(), stdout);
    }
    int n;
    char buf[MAXLINE];
    rio_t rio;
    Rio_readinitb(&rio, connfd);
    // while
    if ((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0)
    {
        std::unique_lock<std::mutex> lock(mtxrser);
        // std::cout << "room[" << sroom << "](" << roomtree[sroom].first[connfd] << ") : " << buf << std::endl;
        std::string s = "";
        s = "room[" + sroom + "](" + roomtree[sroom].first[connfd] + ") : " + buf;
        Fputs(s.c_str(), stdout);

        std::string smsg = "";
        smsg = "<" + roomtree[sroom].first[connfd] + "> : " + buf;
        roomtree[sroom].second.push_back(smsg);

        std::function<void(std::string, int)> cfuntest = newroom;
        thpoor.enqueue(std::bind(cfuntest, sroom, connfd));

        cond.notify_all();
    }
    else
    {
        std::unique_lock<std::mutex> lock(mtxrser);
        roomtree[sroom].first.erase(connfd);
        Close(connfd);
    }
    {
        std::string s1 = sroom + " newroom over!\n";
        Fputs(s1.c_str(), stdout);
    }
}

void workroom(std::string sroom)
{
    Fputs("workroom start!\n", stdout);
    while (1)
    {
        std::unique_lock<std::mutex> lock(mtxrser);
        cond.wait(lock, [&sroom]()
                  { return !roomtree[sroom].second.empty(); });
        if (roomtree[sroom].first.empty())
        {
            roomtree.erase(sroom);
            std::string s = "";
            s = sroom + " over \n";
            Fputs(s.c_str(), stdout);
            break;
        }
        auto &msgs = roomtree[sroom].second;
        std::string Msg = "";
        while (!msgs.empty())
        {
            Msg += msgs.front();
            msgs.pop_front();
        }
        for (auto &[it, name] : roomtree[sroom].first)
        {
            std::string msg = "";
            msg = "[" + name + "] : " + Msg;
            Rio_writen(it, const_cast<char *>(Msg.c_str()), strlen(Msg.c_str()));
            Fputs(msg.c_str(), stdout);
        }
    }
}