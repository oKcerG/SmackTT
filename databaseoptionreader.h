#ifndef DATABASEOPTIONREADER_H
#define DATABASEOPTIONREADER_H

#include "abstractoptionreader.h"
class Database;

class DatabaseOptionReader : public AbstractOptionReader
{
    public:
        DatabaseOptionReader(Database& database);

    protected:
        void readValues();

    private:
        Database& m_database;
};

#endif // DATABASEOPTIONREADER_H
