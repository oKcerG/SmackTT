#ifndef ANNOUNCE_H
#define ANNOUNCE_H
#include <sstream>
#include "option.h"

struct Announce
{
    Announce(const std::string& uri);
    enum Event
    {
        none,
        started,
        stopped,
        completed,
        invalid
    };
    std::string infohash;
    std::string peerid;
    unsigned short port;
    Event event;
    unsigned int uploaded;
    unsigned int downloaded;
    unsigned int left;
    bool compact;
    size_t numwant;
};

template <>
void from_string<Announce::Event>(Announce::Event& value, const std::string& str);

#endif // ANNOUNCE_H
