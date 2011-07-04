#ifndef UTILS_H
#define UTILS_H

#include <string>
namespace utils
{
    int getProcCount();
    std::string decodeUri(const std::string& uri);
    int decodeHex(char v);
    std::string peerString(unsigned long ip, unsigned int port);
}
#endif
