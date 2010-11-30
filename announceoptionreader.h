#ifndef ANNOUNCEOPTIONREADER_H
#define ANNOUNCEOPTIONREADER_H

#include "abstractoptionreader.h"
#include <string>

class AnnounceOptionReader : public AbstractOptionReader
{
    public:
        AnnounceOptionReader(const std::string& announceStr);

    protected:
        void readValues();

    private:
        std::string m_announceStr;
};

#endif // ANNOUNCEOPTIONREADER_H
