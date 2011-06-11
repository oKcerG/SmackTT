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
    int uploaded;
    int downloaded;
    int left;
    bool compact;
    int numwant;
};

template <> void OptionImpl<Announce::Event>::setValue(const std::string& str);

#endif // ANNOUNCE_H
