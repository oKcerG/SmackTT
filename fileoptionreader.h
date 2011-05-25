#ifndef FILEOPTIONREADER_H
#define FILEOPTIONREADER_H

#include "istreamoptionreader.h"
#include <boost/algorithm/string.hpp>

class FileOptionReader : public OptionReader
{
    public:
        FileOptionReader(const std::string& fileName);
        inline static bool ignoreLine(const std::string& key)
        {
            return key.empty() || key[0] == '#';
        }
        inline static void trim(std::string& text)
        {
            boost::trim(text);
        }
        typedef IStreamOptionReader<'=','\n',trim,trim,ignoreLine> FileStreamReader;

    private:
        void doReadOptions(std::map<std::string, std::string>& values);
        std::string m_fileName;
};

#endif // FILEOPTIONREADER_H
