#include "Database.h"
#include <iostream>
//#include "connection.h"
#include "utils.h"
#include "announce.h"
#include "databaseconfig.h"
#include "user.h"
#include "torrent.h"

#include <boost/foreach.hpp>
#define foreach BOOST_FOREACH

Database::Database(const DatabaseConfig& config) : m_connection(config.database().c_str(), config.host().c_str(), config.user().c_str(), config.password().c_str())
{
}

Database::~Database()
{
    //dtor
}

std::string Database::getPeersIP(const std::string& infoHash)
{
    std::string results;
    std::cout << "querying\n";
    mysqlpp::Query query = m_connection.query("SELECT ipa, port FROM xbt_announce_log WHERE info_hash = %0q ORDER BY RAND() LIMIT 5");
    query.parse();
    mysqlpp::StoreQueryResult res = query.store(infoHash);
    for (mysqlpp::StoreQueryResult::iterator it = res.begin(); it != res.end(); it++)
        results += utils::peerString((*it)[0], (*it)[1]);
    return results;
}

std::string Database::getLeechersIP(const std::string& infoHash)
{
    std::string vec;
    return vec;
}

void Database::addAnnounceLog(unsigned long address, const Announce& req)
{
    mysqlpp::Query query = m_connection.query();
    query << "INSERT INTO xbt_announce_log (ipa, port, event, info_hash, peer_id, downloaded, left0, uploaded, uid) VALUES (";
    query << address << ", ";
    query << req.port << ", ";
    query << 0 << ", ";
    query << mysqlpp::quote << req.infohash << ", ";
    query << mysqlpp::quote << req.peerid << ", ";
    query << req.downloaded << ", ";
    query << req.left << ", ";
    query << req.uploaded << ", ";
    query << 0 << ")";
    mysqlpp::SimpleResult res = query.execute();
}


User Database::getUser(const std::string& passkey)
{
    User u;
    u.uid = 0;
    u.can_leech = true;
    return u;
}

Torrent Database::getTorrent(const std::string& infoHash)
{
    Torrent t;
    t.fid = 0;
    return t;
}

void Database::getConfig(std::map<std::string, std::string>& map)
{
    mysqlpp::Query query = m_connection.query("SELECT name, value FROM xbt_config");
    mysqlpp::StoreQueryResult res = query.store();
    foreach (mysqlpp::Row row, res)
        map[row[0].c_str()]  = row[1].c_str();
}
