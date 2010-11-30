#include "databaseoptionreader.h"
#include "database.h"

#include <boost/foreach.hpp>
#define foreach BOOST_FOREACH

DatabaseOptionReader::DatabaseOptionReader(Database& database) : AbstractOptionReader(), m_database(database)
{
}

void DatabaseOptionReader::readValues()
{
    m_database.getConfig(m_values);
}
