#ifndef URIOPTIONREADER_H
#define URIOPTIONREADER_H

#include "abstractoptionreader.h"
#include <string>

class UriOptionReader : public AbstractOptionReader
{
    public:
        UriOptionReader(const std::string& uri);

    protected:
        void readValues();

    private:
        std::string m_uri;
};

#endif // URIOPTIONREADER_H
