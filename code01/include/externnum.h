#ifndef _EXTERNNUM_HPP_
#define _EXTERNNUM_HPP_

extern "C"
{
#include <csapp.h>
}
#include <deque>
#include <map>
#include <set>
#include <mutex>
#include <condition_variable>
#include "threadpoor.hpp"

extern ThreadPool thpoor;

extern std::deque<int> clientdq;
extern std::condition_variable cond;
extern std::mutex mtxroom;
extern std::map<std::string, std::pair<std::map<int, std::string>, std::deque<std::string>>> roomtree;

extern int rservers;
extern std::mutex mtxrser;

#endif