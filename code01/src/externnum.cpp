#include <deque>
#include <map>
#include <set>
#include <mutex>
#include <condition_variable>
#include "../include/threadpoor.hpp"

ThreadPool thpoor(10);

std::deque<int> clientdq;
std::condition_variable cond;
std::condition_variable roomcond;
std::mutex mtxroom;
std::map<std::string, std::pair<std::map<int, std::string>, std::deque<std::string>>> roomtree;

int rservers = 0;
std::mutex mtxrser;

bool run = true;
std::mutex mtxrun;