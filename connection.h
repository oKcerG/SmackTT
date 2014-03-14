#ifndef CONNECTION_H
#define CONNECTION_H

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <string>
#include "announce.h"
#include "bencodedstring.h"

class Server;
class User;
class Torrent;

class Connection : public boost::enable_shared_from_this<Connection>
{
public:
    typedef boost::shared_ptr<Connection> pointer;

    static pointer create(Server &server);
    boost::asio::ip::tcp::socket& socket();
    void start();

protected:
    void handleRequest(const std::string& reques, const unsigned long &ipa);
    void handleAnnounce(const std::string& passkey, const std::string& uri, const unsigned long &ipa);
    //std::string acceptAnnounce(const Announce& announce, const User& user, const Torrent& torrent, const unsigned long &ipa);

private:
    Connection(Server &server);
    void read(const boost::system::error_code& error, std::size_t transferred);
    void write(const boost::system::error_code& error);

    boost::asio::ip::tcp::socket m_socket;
    boost::asio::streambuf m_buffer;
    BencodedString m_response;
    Server &m_server;
};

#endif // CONNECTION_H
