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
    loadTorrents();
    loadUsers();
}

Database::~Database()
{
    //dtor
}

/*
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
*/

User& Database::getUser(const std::string& passkey)
{
    std::unordered_map<std::string, User>::iterator it = m_users.find(passkey);
    if (it == m_users.end())
        throw std::runtime_error("User not found");
    return it->second;
}

Torrent& Database::getTorrent(const std::string& infoHash)
{
    std::unordered_map<std::string, Torrent>::iterator it = m_torrents.find(infoHash);
    if (it == m_torrents.end())
        throw std::runtime_error("Torrent not found");
    return it->second;
}

void Database::getConfig(std::map<std::string, std::string>& map)
{
    mysqlpp::Query query = m_connection.query("SELECT name, value FROM xbt_config");
    mysqlpp::StoreQueryResult res = query.store();
    foreach (mysqlpp::Row& row, res)
    map[row[0].c_str()]  = row[1].c_str();
}


void Database::loadTorrents()
{
    mysqlpp::Query query = m_connection.query("SELECT ID, info_hash, freetorrent, Snatched FROM torrents ORDER BY ID;");
    if(mysqlpp::StoreQueryResult res = query.store())
    {
        m_torrents.reserve(res.size());
        foreach (const mysqlpp::Row& row, res)
        {
           /* unsigned int id = row[0];
            std::string infohash = row[1];
            bool fl = row[2];
            unsigned int completed = row[3];
            Torrent torrent(row[0], row[1], row[2], row[3]);
            torrents[row[2]] = torrent;*/
        }
    }
}

void Database::loadUsers()
{
    mysqlpp::Query query = m_connection.query("SELECT ID, can_leech, torrent_pass FROM users_main WHERE Enabled='1';");
    if(mysqlpp::StoreQueryResult res = query.store())
    {
        m_users.reserve(res.size());
        foreach (const mysqlpp::Row& row, res)
        {
            std::cout << row[2] << "\n";
            m_users.insert(std::make_pair(row[2], User(row[0], row[1])));
        }
    }
}
