#include "../include/setroom.h"

void setroom()
{
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
                cond.wait(lock, []()
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
                    break;
                }
            }
            rio_t rio;
            char buf[MAXLINE];
            Rio_readinitb(&rio, connfd);
            int n = Rio_readlineb(&rio, buf, MAXLINE);
            if (n < 0)
                continue;
            std::stringstream sio(buf);

            sio >> sroom >> name;
        }

        { /*保护roomtree*/
            std::unique_lock<std::mutex> lock(mtxrser);
            if (isroom)
            {
                if (roomtree.find(sroom) == roomtree.end())
                {
                    ++rservers;
                    roomtree[sroom] = {{}, {}};

                    std::function<void(std::string)> sfuntest = workroom;
                    thpoor.enqueue(std::bind(sfuntest, sroom));
                }
                roomtree[sroom].first.insert({connfd, name});
                std::function<void(std::string, int)> cfuntest = newroom;
                thpoor.enqueue(std::bind(cfuntest, sroom, connfd));
            }
        }
    }
}
