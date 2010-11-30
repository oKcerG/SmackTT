#include "databaseconfig.h"
#include "fileoptionreader.h"
#include <sstream>
#include <iostream>
#include "option.h"

DatabaseConfig::DatabaseConfig()
{
    FileOptionReader options("xbt_tracker.conf");
    options.addOption("mysql_host", true, m_host)
           .addOption("mysql_user", true, m_user)
           .addOption("mysql_password", true, m_password)
           .addOption(optPointer(new Option<std::string>("mysql_database", true, m_database)));
    options.readOptions();
}
