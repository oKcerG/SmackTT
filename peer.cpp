#include "peer.h"
#include <ctime>

Peer::Peer(unsigned int uid, const std::string& uagent, const std::string& peerString) :
    userid(uid),
    user_agent(uagent),
    ip_port(peerString),
    uploaded(0),
    downloaded(0),
    left(0),
    last_announced(0),
    first_announced(time(0)),
    announces(0)
{

}
