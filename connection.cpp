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
#include "istreamoptionreader.h"
#include "optionmanager.h"
#include "user.h"
#include <ctime>
#include "torrent.h"
#include <boost/algorithm/string.hpp>

#define foreach BOOST_FOREACH

namespace ba = boost::asio;

std::ostream& operator<<(std::ostream& stream, const std::map<std::string,std::string>& map)
{
    typedef std::pair<std::string, std::string> string_pair;
    foreach (const string_pair& pair, map)
    {
        stream.width(15);
        stream << pair.first << " : " << pair.second << std::endl;
    }
    return stream;
}

inline void trim_left(std::string& text)
{
    boost::trim_left(text);
}

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

void Connection::read(const boost::system::error_code& error, std::size_t /*tranferred*/)
{
    if (error)
        std::cerr << "Connection read error : " << error.message() << std::endl;

    std::istream is(&m_buffer);

    std::string uri;
    is.ignore(5); // ignore "GET /"
    is >> uri;
    is.ignore(11); // ignore " HTTP/1.1\r\n"

    std::cout << "\n# HTTP URI :\n" << uri<< "\n";

    IStreamOptionReader<':','\n', doNothing, trim_left> headersReader(is);
    std::map<std::string, std::string> headers;
    headersReader.readOptions(headers);

    std::cout << "\n# HTTP HEADERS :\n" << headers;

    ba::ip::tcp::endpoint endpoint = m_socket.remote_endpoint();
    ba::ip::address_v4 address = endpoint.address().to_v4();


    handleRequest(uri, address.to_ulong());

    ba::async_write(m_socket, ba::buffer("HTTP/1.1 200 OK\r\n\r\n" + m_response.str()),
                    boost::bind(&Connection::write, shared_from_this(), ba::placeholders::error));
}

void Connection::write(const boost::system::error_code& error)
{
    if (error)
        std::cout << "Connection write error : " << error.message() << std::endl;
}

void Connection::handleRequest(const std::string& request, const unsigned long &ipa)
{
    m_response << BencodedString::beginDic;
    try
    {
        size_t pos = 0;
        std::string passkey;
        if (request.length() > 33)
        {
            if (request[32] == '/')
            {
                passkey = request.substr(0, 32);
                std::cout << "\n# PASSKEY : " << passkey << std::endl;
                pos = 33;
            }
            else
                throw std::runtime_error("Ill-formed request, where is the passkey ?");
        }
        else
            throw std::runtime_error("request too short");
        size_t pos2 = request.find('?', pos);
        if (pos2 == std::string::npos)
            throw std::runtime_error("method not found!");
        std::string method = request.substr(pos, pos2 - pos);
        pos2++;
        std::cout << "\n# METHOD : " << method << std::endl;
        std::string uri = request.substr(pos2, request.length() - pos2);
        if (method == "announce")
            handleAnnounce(passkey, uri, ipa);
    }
    catch (std::exception& e)
    {
        m_response << "failure reason" << e.what();
    }

    m_response << BencodedString::end;
}

void Connection::handleAnnounce(const std::string& passkey, const std::string& uri, const unsigned long &ipa)
{
    std::cout << "\n# ANNOUNCE :\n";
    Announce announce(uri);
    Database& database = m_server.database();
    std::shared_ptr<User> user = database.getUser(passkey);
    std::shared_ptr<Torrent> torrent = database.getTorrent(announce.infohash);

    std::cout << "getTorrent\n";

    bool leecher = announce.left > 0;
    auto& supposedContainer = leecher ? torrent->leechers : torrent->seeders;
    auto& otherContainer = leecher ? torrent->seeders : torrent->leechers;
    //typedef (decltype(supposedContainer))::value_type PeerPair;

    long long uploaded = 0;
    long long downloaded = 0;
    if (announce.event == Announce::stopped)
    {
        announce.numwant = 0;
        auto peerIterator = supposedContainer.find(announce.peerid);
        if (peerIterator != supposedContainer.end()) // Peer found where it should be
        {
            uploaded = peerIterator->second.uploaded;
            downloaded = peerIterator->second.downloaded;
            supposedContainer.erase(peerIterator);
        }
        else if ((peerIterator = otherContainer.find(announce.peerid)) != otherContainer.end())  // Peer found where it shouldn't be
        {
            uploaded = peerIterator->second.uploaded;
            downloaded = peerIterator->second.downloaded;
            otherContainer.erase(peerIterator);
        }
    }
    else
    {
        auto peerIterator = supposedContainer.find(announce.peerid);
        if (peerIterator == supposedContainer.end()) // Peer not found where it should be
        {
            std::pair<decltype(peerIterator), bool> pair;
            peerIterator = otherContainer.find(announce.peerid);
            if (peerIterator == otherContainer.end()) // Peer not found anywhere
            {
                std::cout << "Peer not found anywhere" << std::endl;
                pair = supposedContainer.insert(std::make_pair(announce.peerid, Peer(user->uid, "", utils::peerString(ipa, announce.port))));
            }
            else // Peer found where it shouldn't be
            {
                std::cout << "Peer found where it shouldn't be" << std::endl;
                pair = supposedContainer.insert(std::make_pair(announce.peerid, peerIterator->second));
                otherContainer.erase(peerIterator);
            }
            if (!pair.second)
                throw std::runtime_error("Can't insert the peer");
            peerIterator = pair.first;
        }
        else
        {
            std::cout << "Peer found where it should be" << std::endl;
        }
    }

    //database.addAnnounceLog(ipa, a);
    size_t numpeers = 0;
    std::string peersIP;
    if (true || leecher)
    {
        foreach (auto pair, torrent->seeders)
        {
            if (numpeers >= announce.numwant)
                break;

            auto& peer = pair.second;
            if (peer.userid == user->uid)
                continue;
            peersIP += peer.ip_port;
            ++numpeers;
        }
    }

    foreach (auto pair, torrent->leechers)
    {
        if (numpeers >= announce.numwant)
            break;

        auto& peer = pair.second;
        if (peer.userid == user->uid)
            continue;
        peersIP += peer.ip_port;
        ++numpeers;
    }

    m_response << "warning message" << "This tracker is in developement";
    m_response << "interval" << m_server.config().announce_interval();
    m_response << "min interval" << m_server.config().announce_interval();
    m_response << "complete" << torrent->seeders.size();
    m_response << "incomplete" << torrent->leechers.size();
    m_response << "peers";
    //peersIP = m_server.database().getPeersIP(req.infohash);
    m_response << peersIP;
}

std::string Connection::acceptAnnounce(const Announce& announce, const User& user, const Torrent& torrent, const unsigned long &ipa)
{
    /*if (!m_server.config().offline_message().empty())
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
    }*/
    // to do :
    // torrent limit
    // peer limit
    // Client whitelist
    return "";
}
