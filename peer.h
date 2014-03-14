#ifndef PEER_INCLUDED
#define PEER_INCLUDED

#include <string>

struct Peer
{
    Peer(unsigned int uid, const std::string& uagent, const std::string& peerString);
	unsigned int userid;
	std::string user_agent;
	std::string ip_port;
	long long uploaded;
	long long downloaded;
	uint64_t left;
	time_t last_announced;
	time_t first_announced;
	unsigned int announces;
};

#endif // PEER_INCLUDED
