extern "C"
{
#include <csapp.h>
}
#include <iostream>
#include <thread>
#include <mutex>

void msgwrite(int clientfd);

void msgread();

char bufr[MAXLINE];
char bufw[MAXLINE];
rio_t rio;
std::mutex mut;

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        fprintf(stderr, "%s\n", argv[0]);
        exit(0);
    }
    char *host = argv[1];
    char *port = argv[2];

    int clientfd = Open_clientfd(host, atoi(port));
    Rio_readinitb(&rio, clientfd);
    // std::cin.getline(buf, MAXLINE, '\n');
    char buf[MAXLINE] = "";
    Fgets(buf, MAXLINE, stdin);
    Rio_writen(clientfd, buf, strlen(buf));

    std::thread tw(msgwrite, clientfd);
    std::thread tr(msgread);

    /*
    while (Fgets(buf, MAXLINE, stdin) != NULL)
    {
        Rio_writen(clientfd, buf, strlen(buf));
        Rio_readlineb(&rio, buf, MAXLINE);
        // std::cout << "getbuf: " << buf << std::endl;
        std::string s = "getbuf: ";
        s += buf;
        s += "\n";
        Fputs(s.c_str(), stdout);
    }
    */
    tw.join();
    tr.join();
    Close(clientfd);
    exit(0);
}

void msgwrite(int clientfd)
{
    while (1)
    {

        Fgets(bufw, MAXLINE, stdin);

        Rio_writen(clientfd, bufw, strlen(bufw));
    }
}

void msgread()
{
    while (1)
    {
        Rio_readlineb(&rio, bufr, MAXLINE);
        // std::cout << "getbuf: " << buf << std::endl;
        std::string s = "getbuf: ";
        s += bufr;
        Fputs(s.c_str(), stdout);
    }
}