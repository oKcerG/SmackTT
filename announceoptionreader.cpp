#include "announceoptionreader.h"
#include "utils.h"
#include <iostream>

AnnounceOptionReader::AnnounceOptionReader(const std::string& announceStr) : m_announceStr(announceStr)
{
    //ctor
}

void AnnounceOptionReader::doReadOptions()
{
    size_t pos = 0;
    if (m_announceStr.length() > 34)
    {
        if (m_announceStr[33] == '/')
        {
            m_values["passkey"] = m_announceStr.substr(1, 32);
            pos = 34;
        }
    }
    size_t pos2 = m_announceStr.find('?', pos);
    if (pos == std::string::npos)
        std::cerr << "method not found!\n";
    m_values["method"] = m_announceStr.substr(pos, pos2 - pos);
    std::string key, value;
    bool keyFound = false;
    for (size_t i = pos; i < m_announceStr.length(); i++)
    {
        if (!keyFound)
        {
            if (m_announceStr[i] == '=')
                keyFound = true;
            else
                key += m_announceStr[i];
        }
        else
        {
            if (m_announceStr[i] == '&')
            {
                m_values[key] = utils::decodeUri(value);
                key.clear();
                value.clear();
                keyFound = false;
            }
            else
            {
                value += m_announceStr[i];
            }
        }
    }
}
