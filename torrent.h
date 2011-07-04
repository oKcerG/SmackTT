#ifndef TORRENT_H
#define TORRENT_H

#include "peer.h"

struct Torrent
{
    Torrent (unsigned int id, const std::string& ih, bool fl, unsigned int c) :
        fid(id),
        info_hash(ih),
        free_torrent(fl),
        completed(c),
        balance(0)
    {

    }
    unsigned int fid;
    std::string info_hash;
    unsigned int completed;
    unsigned long long balance;
    bool free_torrent;
    //time_t last_seeded;
    std::map<std::string, Peer> seeders;
    std::map<std::string, Peer> leechers;
};

#endif // TORRENT_H
