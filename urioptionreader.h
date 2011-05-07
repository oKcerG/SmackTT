#ifndef URIOPTIONREADER_H
#define URIOPTIONREADER_H

#include "optionreader.h"
#include <string>

class UriOptionReader : public OptionReader
{
    public:
        UriOptionReader(const std::string& uri);

    protected:
        void readOptions();

    private:
        std::string m_uri;
};

#endif // URIOPTIONREADER_H
