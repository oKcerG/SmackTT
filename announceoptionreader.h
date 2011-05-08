#ifndef ANNOUNCEOPTIONREADER_H
#define ANNOUNCEOPTIONREADER_H

#include "optionreader.h"
#include <string>

class AnnounceOptionReader : public OptionReader
{
    public:
        AnnounceOptionReader(const std::string& announceStr);

    private:
        void doReadOptions();
        std::string m_announceStr;
};

#endif // ANNOUNCEOPTIONREADER_H
