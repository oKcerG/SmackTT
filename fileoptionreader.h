#ifndef FILEOPTIONREADER_H
#define FILEOPTIONREADER_H

#include "optionreader.h"
#include <string>

class FileOptionReader : public OptionReader
{
    public:
        FileOptionReader(const std::string& fileName);

    private:
        void doReadOptions(std::map<std::string, std::string>& values);
        std::string m_fileName;
};

#endif // FILEOPTIONREADER_H
