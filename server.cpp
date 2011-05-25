#include "server.h"
#include <iostream>
#include "database.h"
#include "Config.h"
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include "databaseconfig.h"
#include <vector>
#include <algorithm>
namespace ba = boost::asio;

Server::Server() : m_dbConfig(),
                   m_database(m_dbConfig),
                   m_config(m_database),
                   m_service(),
                   m_acceptor(m_service, ba::ip::tcp::endpoint(ba::ip::tcp::v4(), m_config.listen_port()))
{
    m_config.read();
}


Server::~Server()
{
}


const Config& Server::config()
{
    return m_config;
}


Database& Server::database()
{
    return m_database;
}


boost::asio::io_service& Server::service()
{
    return m_service;
}


void Server::run()
{
    listen();
    m_service.run();
}


void Server::listen()
{
    Connection::pointer connection = Connection::create(*this);
    m_acceptor.async_accept(connection->socket(),
                            boost::bind(&Server::accept, this, connection,
                                        ba::placeholders::error));
}


void Server::accept(Connection::pointer connection, const boost::system::error_code& error)
{
    std::string ip = connection->socket().remote_endpoint().address().to_v4().to_string();
    std::cout << "-----------------------------------------\n";
    std::cout << "New request coming from " << ip << std::endl;
    if (!error)
        connection->start();
    else
        std::cout << "Server accept error : " << error.message() << std::endl;
    listen();
}
