#ifndef DATABASE_H
#define DATABASE_H

#include <mysql++.h>
#include <vector>
#include <string>

class DatabaseConfig;
class Announce;
class User;
class Torrent;

class Database
{
    public:
        Database(const DatabaseConfig& config);
        ~Database();

        std::string getPeersIP(const std::string& infoHash);
        std::string getLeechersIP(const std::string& infoHash);
        User getUser(const std::string& passkey);
        Torrent getTorrent(const std::string& infoHash);
        void addAnnounceLog(unsigned long address, const Announce& request);
        void getConfig(std::map<std::string, std::string>& map);

    protected:

    private:
        mysqlpp::Connection m_connection;
};

#endif // DATABASE_H
