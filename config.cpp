#include "config.h"
#include "option.h"
#include "fileoptionreader.h"
#include "databaseoptionreader.h"
#include <fstream>
#include <stdexcept>

Config::Config(Database& database)
{
    m_manager.addReader(new FileOptionReader("smacktt.conf"));
    m_manager.addReader(new DatabaseOptionReader(database));

    m_manager.addOption("announce_interval", m_announce_interval, 1)
    .addOption("anonymous_announce", m_anonymous_announce, true)
    .addOption("anonymous_connect", m_anonymous_connect, true)
    .addOption("anonymous_scrape", m_anonymous_scrape, true)
    .addOption("auto_register", m_auto_register, true)
    .addOption("clean_up_interval", m_clean_up_interval, 1)
    .addOption("daemon", m_daemon, true)
    .addOption("debug", m_debug, false)
    .addOption("full_scrape", m_full_scrape, false)
    .addOption("gzip_debug", m_gzip_debug, true)
    .addOption("gzip_scrape", m_gzip_scrape, true)
    .addOption("listen_ipa", m_listen_ipa, std::string())
    .addOption("listen_port", m_listen_port, 2710)
    .addOption("log_access", m_log_access, false)
    .addOption("log_announce", m_log_announce, false)
    .addOption("log_scrape", m_log_scrape, false)
    .addOption("offline_message", m_offline_message, "")
    .addOption("pid_file", m_pid_file, "xbt_tracker.pid")
    .addOption("read_config_interval", m_read_config_interval, 60)
    .addOption("read_db_interval", m_read_db_interval, 60)
    .addOption("redirect_url", m_redirect_url, "")
    .addOption("scrape_interval", m_scrape_interval, 0)
    .addOption("table_announce_log", m_table_announce_log, "xbt_announce_log")
    .addOption("table_files", m_table_files, "xbt_files")
    .addOption("table_files_users", m_table_files_users, "xbt_files_users")
    .addOption("table_scrape_log", m_table_scrape_log, "xbt_scrape_log")
    .addOption("table_users", m_table_users, "xbt_users")
    .addOption("write_db_interval", m_write_db_interval, 15);
}

void Config::read()
{
    m_manager.readOptions();
}
