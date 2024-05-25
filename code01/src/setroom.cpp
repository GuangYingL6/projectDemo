#include "../include/setroom.h"

void setroom()
{
    {
        Fputs("setroom start!\n", stdout);
    }
    while (1)
    {

        /*分组*/
        std::string sroom = "";
        std::string name = "nullname";
        bool isroom = false;
        int connfd = -1;

        while (1)
        {
            { /*连接队列访问保护*/
                std::unique_lock<std::mutex> lock(mtxroom);
                roomcond.wait(lock, []()
                              { return !clientdq.empty(); });

                if (!clientdq.empty())
                {
                    connfd = clientdq.front();
                    clientdq.pop_front();
                    isroom = true;
                }
                else
                {
                    isroom = false;
                    connfd = -1;
                    continue;
                }
            }
            rio_t rio;
            char buf[MAXLINE];
            Rio_readinitb(&rio, connfd);
            int n = Rio_readlineb(&rio, buf, MAXLINE);
            if (n < 0)
                continue;
            std::stringstream sio;
            sio << buf;
            sio >> sroom >> name;
            // std::cout << sroom << " " << name << std::endl;

            {
                std::string s = " ";
                s = sroom + s + name + "\n";
                Fputs(s.c_str(), stdout);
            }
            if (isroom)
            {
                break;
            }
        }

        { /*保护roomtree*/
            std::unique_lock<std::mutex> lock(mtxrser);
            if (isroom)
            {
                bool ff = false;
                if (roomtree.find(sroom) == roomtree.end())
                {
                    ff = true;
                }
                roomtree[sroom].first.insert({connfd, name});
                std::function<void(std::string, int)> cfuntest = newroom;
                thpoor.enqueue(std::bind(cfuntest, sroom, connfd));
                if (ff)
                {
                    ++rservers;
                    roomtree[sroom] = {{}, {}};

                    std::function<void(std::string)> sfuntest = workroom;
                    thpoor.enqueue(std::bind(sfuntest, sroom));
                }
            }
        }
    }
}
