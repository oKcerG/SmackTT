#ifndef USER_H
#define USER_H

#include <string>

struct User
{
    int uid;
 	int torrent_pass_version;
 	bool can_leech;
	int wait_time;
	int peers_limit;
	int torrents_limit;
	std::string torrent_pass;
 	unsigned long int downloaded;
 	unsigned long int uploaded;
};

#endif // USER_H
