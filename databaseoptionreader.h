#ifndef DATABASEOPTIONREADER_H
#define DATABASEOPTIONREADER_H

#include "optionreader.h"
class Database;

class DatabaseOptionReader : public OptionReader
{
    public:
        DatabaseOptionReader(Database& database);
        void readOptions();

    private:
        Database& m_database;
};

#endif // DATABASEOPTIONREADER_H
