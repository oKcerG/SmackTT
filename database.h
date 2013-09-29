#ifndef DATABASE_H
#define DATABASE_H

#include <mysql++.h>
#include <vector>
#include <string>
#include <unordered_map>
#include <memory>
#include "user.h"
#include "torrent.h"

class DatabaseConfig;
class Announce;
class User;
class Torrent;

class Database
{
    public:
        Database(const DatabaseConfig& config);
        ~Database();

        std::shared_ptr<User> getUser(const std::string& passkey);
        std::shared_ptr<Torrent> getTorrent(const std::string& infoHash);
        void getConfig(std::map<std::string, std::string>& map);

    private:
        void loadTorrents();
        void loadUsers();
        mysqlpp::Connection m_connection;
        std::unordered_map<std::string, std::shared_ptr<User> > m_users;
        std::unordered_map<std::string, std::shared_ptr<Torrent> > m_torrents;
};

#endif // DATABASE_H
