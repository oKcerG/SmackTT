#ifndef URIOPTIONREADER_H
#define URIOPTIONREADER_H

#include "optionreader.h"
#include <string>

class UriOptionReader : public OptionReader
{
    public:
        UriOptionReader(const std::string& uri);

    private:
        void doReadOptions(std::map<std::string, std::string>& values);
        std::string m_uri;
};

#endif // URIOPTIONREADER_H
