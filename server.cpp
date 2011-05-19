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
    std::cout << "Server construct\n";
    m_config.read();
}


Server::~Server()
{
    std::cout << "Server destruct\n";
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
    std::cout << "Server listen\n";
    Connection::pointer connection = Connection::create(*this);
    m_acceptor.async_accept(connection->socket(),
                            boost::bind(&Server::accept, this, connection,
                                        ba::placeholders::error));
}


void Server::accept(Connection::pointer connection, const boost::system::error_code& error)
{
    static std::vector<std::string> vec;
    std::cout << "Server accept\n";
    std::string ip = connection->socket().remote_endpoint().address().to_v4().to_string();
    //if (std::find(vec.begin(), vec.end(), ip) == vec.end())
    {
        std::cout << ip << std::endl;
        //vec.push_back(ip);
    }
    if (!error)
        connection->start();
    else
        std::cout << "Server accept error : " << error.message() << std::endl;
    listen();
}
