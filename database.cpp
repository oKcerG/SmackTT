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
    /*mysqlpp::Query query = m_connection.query("SELECT ID, info_hash, freetorrent, Snatched FROM torrents ORDER BY ID;");
	if(mysqlpp::StoreQueryResult res = query.store()) {
		mysqlpp::String one("1"); // Hack to get around bug in mysql++3.0.0
		size_t num_rows = res.num_rows();
		for(size_t i = 0; i < num_rows; i++) {
			std::string info_hash;
			res[i][1].to_string(info_hash);

			torrent t;
			t.id = res[i][0];
			if(res[i][2].compare(one) == 0) {
				t.free_torrent = true;
			} else {
				t.free_torrent = false;
			}
			t.balance = 0;
			t.completed = res[i][3];
			t.last_selected_seeder = "";
			torrents[info_hash] = t;
		}
	}*/
}

void loadUsers()
{

}
