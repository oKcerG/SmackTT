#ifndef TORRENT_H
#define TORRENT_H

struct Torrent
{
    int fid;
    std::string info_hash;
 	int leechers;
 	int seeders;
 	int completed;
 	int flags;
 	int mtime;
 	int ctime;
};

#endif // TORRENT_H
