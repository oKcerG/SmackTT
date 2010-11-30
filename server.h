#ifndef SERVER_H
#define SERVER_H

#include <boost/asio.hpp>
#include "databaseconfig.h"
#include "database.h"
#include "config.h"
#include "connection.h"

class Server
{
public:
    Server();
    ~Server();
    boost::asio::io_service& service();
    const Config& config();
    Database& database();

private:
    void listen();
    void accept(Connection::pointer connection, const boost::system::error_code& error);

    DatabaseConfig m_dbConfig;
    Database m_database;
    Config m_config;
    boost::asio::io_service m_service;
    boost::asio::ip::tcp::acceptor m_acceptor;
};

#endif // SERVER_H
