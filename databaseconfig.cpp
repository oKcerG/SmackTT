#include "databaseconfig.h"
#include "fileoptionreader.h"
#include <sstream>
#include <iostream>
#include "option.h"

DatabaseConfig::DatabaseConfig()
{
    FileOptionReader options("xbt_tracker.conf");
    options.addOption("mysql_host", m_host)
           .addOption("mysql_user", m_user)
           .addOption("mysql_password", m_password)
           .addOption("mysql_database", m_database);
    options.readOptions();
}
