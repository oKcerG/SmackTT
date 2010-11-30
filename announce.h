#ifndef ANNOUNCE_H
#define ANNOUNCE_H
#include <iostream>

struct Announce
{
    std::string infohash;
    std::string peerid;
    unsigned short port;
    std::string event;
    int uploaded;
    int downloaded;
    int left;
    bool compact;
    int numwant;
};

#endif // ANNOUNCE_H
