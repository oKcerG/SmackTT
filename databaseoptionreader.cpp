#include "databaseoptionreader.h"
#include "database.h"

#include <boost/foreach.hpp>
#define foreach BOOST_FOREACH

DatabaseOptionReader::DatabaseOptionReader(Database& database) : m_database(database)
{
}

void DatabaseOptionReader::readOptions()
{
    m_database.getConfig(m_values);
}
