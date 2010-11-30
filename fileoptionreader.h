#ifndef FILEOPTIONREADER_H
#define FILEOPTIONREADER_H

#include "abstractOptionReader.h"
#include <string>


class FileOptionReader : public AbstractOptionReader
{
    public:
        FileOptionReader(const std::string& fileName);

    protected:
        void readValues();

    private:
        std::string m_fileName;
};

#endif // FILEOPTIONREADER_H
