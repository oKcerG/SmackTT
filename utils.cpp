#include "utils.h"
#include "windows.h"
#include <iostream>
#include <boost/any.hpp>

int utils::getProcCount()
{
    int count = -1;
#ifdef _WIN32
    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    count = sysinfo.dwNumberOfProcessors;
#endif
    return count;
}

int utils::decodeHex(char c)
{
    if (c >= '0' && c <= '9')
        return c - '0';
    if (c >= 'A' && c <= 'F')
        return c - 'A' + 10;
    if (c >= 'a' && c <= 'f')
        return c - 'a' + 10;
    return -1;
}

std::string utils::decodeUri(const std::string& uri)
{
    std::string decoded;
    decoded.reserve(uri.length());
    for (size_t i = 0; i < uri.length(); i++)
    {
        char c = uri[i];
        if (c == '%')
        {
            if (i+2 >= uri.length())
                return "";
            c = decodeHex(uri[i+1])*16 + decodeHex(uri[i+2]);
            i+=2;
        }
        decoded += c;
    }
    return decoded;
}

std::string utils::peerString(unsigned long ip, unsigned int port)
{
    std::string result;

    result += (unsigned char)(ip >> 24);
    result += (unsigned char)(ip >> 16);
    result += (unsigned char)(ip >> 8);
    result += (unsigned char)(ip);

    result += (unsigned char)(port >> 8);
    result += (unsigned char)(port);

    return result;
}
