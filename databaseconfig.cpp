#include "databaseconfig.h"
#include "optionmanager.h"
#include "fileoptionreader.h"
#include <sstream>
#include <iostream>
#include "option.h"

DatabaseConfig::DatabaseConfig()
{
    OptionManager options(new FileOptionReader("database.conf"));
    options.addOption("mysql_host", m_host)
           .addOption("mysql_user", m_user)
           .addOption("mysql_password", m_password)
           .addOption("mysql_database", m_database);
    options.readOptions();
}
