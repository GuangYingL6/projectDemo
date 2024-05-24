#include <deque>
#include <map>
#include <set>
#include <mutex>
#include <condition_variable>
#include "../include/threadpoor.hpp"

ThreadPool thpoor(8);

std::deque<int> clientdq;
std::condition_variable cond;
std::mutex mtxroom;
std::map<std::string, std::pair<std::map<int, std::string>, std::deque<std::string>>> roomtree;

int rservers = 0;
std::mutex mtxrser;
