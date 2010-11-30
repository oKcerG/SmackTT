#include "fileoptionreader.h"
#include <fstream>
#include <boost/algorithm/string.hpp>

FileOptionReader::FileOptionReader(const std::string& fileName) : m_fileName(fileName)
{
}

void FileOptionReader::readValues()
{
    std::ifstream fileStream(m_fileName.c_str(), std::ifstream::in);
    std::string line;
    size_t pos;
    std::string name, value;
    while (fileStream.good())
    {
        std::getline (fileStream, line);

        pos = line.find('=');
        name = line.substr(0, pos);
        pos++;
        value = line.substr(pos, line.length() - pos);
        boost::trim(name);
        boost::trim(value);
        //if (!name.empty() && name[0] != '#')
            m_values[name] = value;
    }
    fileStream.close();
}