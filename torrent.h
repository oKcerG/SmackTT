#ifndef TORRENT_H
#define TORRENT_H

#include "peer.h"

struct Torrent
{
    unsigned int fid;
    std::string info_hash;
 	unsigned int completed;
	unsigned long long balance;
    bool free_torrent;
	time_t last_seeded;
	std::map<std::string, Peer> seeders;
	std::map<std::string, Peer> leechers;
};

#endif // TORRENT_H
