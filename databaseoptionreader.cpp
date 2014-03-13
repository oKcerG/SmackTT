#include "databaseoptionreader.h"
#include "database.h"

DatabaseOptionReader::DatabaseOptionReader(Database& database) : m_database(database)
{
}

void DatabaseOptionReader::doReadOptions(std::map<std::string, std::string>& values)
{
    m_database.getConfig(values);
}
