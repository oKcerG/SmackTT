#include "connection.h"
#include "utils.h"
#include "bencodedstring.h"
#include <sstream>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/foreach.hpp>
#include "server.h"
#include "config.h"
#include "database.h"
#include "urioptionreader.h"
#include "user.h"
#include <ctime>
#include "torrent.h"

#define foreach BOOST_FOREACH

namespace ba = boost::asio;

Connection::Connection(Server& server) : m_socket(server.service()), m_server(server)
{
}

Connection::pointer Connection::create(Server& server)
{
    return pointer(new Connection(server));
}

ba::ip::tcp::socket& Connection::socket()
{
    return m_socket;
}

void Connection::start()
{
    ba::async_read_until(m_socket, m_buffer, "\r\n\r\n",
                         boost::bind(&Connection::read, shared_from_this(),
                                     ba::placeholders::error,
                                     ba::placeholders::bytes_transferred));
}

void Connection::read(const boost::system::error_code& error, std::size_t transferred)
{
    if (error)
        std::cerr << "Connection read error : " << error.message() << std::endl;
    std::istream is(&m_buffer);
    std::string get, request;
    is >> get >> request;
    ba::ip::tcp::endpoint endpoint = m_socket.remote_endpoint();
    ba::ip::address_v4 address = endpoint.address().to_v4();
    handleRequest(request, address.to_ulong());
    ba::async_write(m_socket, ba::buffer(m_response),
                    boost::bind(&Connection::write, shared_from_this(), ba::placeholders::error));
    std::cout << "\n--------------------------------------\n\n";
}

void Connection::write(const boost::system::error_code& error)
{
    if (error)
        std::cout << "Connection write error : " << error.message() << std::endl;
}

void Connection::handleRequest(const std::string& request, const unsigned long &ipa)
{
    size_t pos = 1;
    std::string passkey;
    if (request.length() > 34)
    {
        if (request[33] == '/')
        {
            passkey = request.substr(1, 32);
            pos = 34;
        }
    }
    size_t pos2 = request.find('?', pos);
    if (pos2 == std::string::npos)
        std::cerr << "method not found!\n";
    std::string method = request.substr(pos, pos2 - pos);
    pos2++;
    std::cout << method << std::endl;
    std::string uri = request.substr(pos2, request.length() - pos2);
    if (method == "announce")
        handleAnnounce(passkey, uri, ipa);
}

void Connection::handleAnnounce(const std::string& passkey, const std::string& uri, const unsigned long &ipa)
{
    std::cout << "handleAnnounce\n";
    m_response = "HTTP/1.1 200 OK\r\n\r\n";
    std::string error;
    try
    {
        Announce a = parseAnnounce(uri);
        //User u = m_server.database().getUser(passkey);
        //Torrent t = m_server.database().getTorrent(a.infohash);
        m_server.database().addAnnounceLog(ipa, a);
        //std::string error = acceptAnnounce();
    }
    catch (AbstractOptionReader::OptionNotFound& e)
    {
        error = "field \"" + e.name() + "\" not found";
    }
    BencodedString bestr;
    bestr << BencodedString::beginDic;
    error = "GrecKo <3 Oinkmeup, and vice versa héhéhé :D lol";
    if (!error.empty())
    {
        bestr << "failure reason" << error;
    }
    else
    {
        bestr << "warning message" << "This tracker is in developement";
        bestr << "interval" << m_server.config().announce_interval();
        bestr << "min interval" << m_server.config().announce_interval();
        bestr << "complete" << 69;
        bestr << "incomplete" << 51;
        bestr << "peers";
        std::string peersIP;
        //peersIP = m_server.database().getPeersIP(req.infohash);
        bestr << peersIP;;
    }
    bestr << BencodedString::end;
    m_response += bestr.str();
}

Announce Connection::parseAnnounce(const std::string& uri)
{
    UriOptionReader options(uri);
    Announce a;
    a.compact = true;
    a.event = "none";
    a.numwant = 0;
    options.addOption("info_hash", true, a.infohash)
           .addOption("peer_id", true, a.peerid)
           .addOption("port", true, a.port)
           .addOption("uploaded", true, a.uploaded)
           .addOption("downloaded", true, a.downloaded)
           .addOption("left", true, a.left)
           .addOption("compact", false, a.compact)
           .addOption("event", false, a.event)
           .addOption("numwant", false, a.numwant);
    options.readOptions();
    std::cout << "info : " << a.infohash << std::endl;
    std::cout << "port : " << a.port << std::endl;
    std::cout << "event : " << a.event << std::endl;
    return a;
}

std::string Connection::acceptAnnounce(const Announce& announce, const User& user, const Torrent& torrent, const unsigned long &ipa)
{
    if (!m_server.config().offline_message().empty())
        return m_server.config().offline_message();
    if (!user.uid && !m_server.config().anonymous_announce())
        return "unregistered torrent pass";
    if (!torrent.fid && !m_server.config().auto_register())
        return "unregistered torrent";
    if (!user.can_leech && announce.left)
        return "access denied, leeching forbidden, you are only allowed to seed";
    time_t remaining = user.wait_time + torrent.ctime - time(0);
    if (announce.left &&  remaining > 0)
    {
        std::ostringstream stream;
        stream << remaining/60;
        std::string error = "access denied, you must wait ";
        error += stream.str();
        error += " minute(s) before downloading this torrent";
        return error;
    }
    // to do :
    // torrent limit
    // peer limit
    return "";
}

std::string Connection::bencodedAnounceResponse(const std::string& passkey, const Announce& req) const
{
    BencodedString bstr;
    bstr << BencodedString::beginDic;
    bstr << "warning message" << "This tracker is in developement";
    bstr << "interval" << m_server.config().announce_interval();
    bstr << "min interval" << m_server.config().announce_interval();
    bstr << "complete" << 69;
    bstr << "incomplete" << 51;
    bstr << "peers";
    bstr << m_server.database().getPeersIP(req.infohash);
    bstr << BencodedString::end;
    return bstr.str();
}
