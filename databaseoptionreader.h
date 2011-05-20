#ifndef DATABASEOPTIONREADER_H
#define DATABASEOPTIONREADER_H

#include "optionreader.h"
class Database;

class DatabaseOptionReader : public OptionReader
{
    public:
        DatabaseOptionReader(Database& database);

    private:
        void doReadOptions(std::map<std::string, std::string>& values);
        Database& m_database;
};

#endif // DATABASEOPTIONREADER_H
