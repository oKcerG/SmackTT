#include "config.h"
#include "database.h"
#include "option.h"

Config::Config(Database& database) : m_fOption("xbt_tracker.conf"), m_dbOption(database)
{
    // default values
    m_announce_interval = 1800;
    m_anonymous_announce = true;
    m_anonymous_connect = true;
    m_anonymous_scrape = true;
    m_auto_register = true;
    m_clean_up_interval = 1;
    m_daemon = true;
    m_debug = false;
    m_full_scrape = false;
    m_gzip_debug = true;
    m_gzip_scrape = true;
    m_listen_ipa = "";
    m_listen_port = 2710;
    m_log_access = false;
    m_log_announce = false;
    m_log_scrape = false;
    m_offline_message = "";
    m_pid_file = "xbt_tracker.pid";
    m_read_config_interval = 60;
    m_read_db_interval = 60;
    m_redirect_url = "";
    m_scrape_interval = 0;
    m_table_announce_log = "xbt_announce_log";
    m_table_files = "xbt_files";
    m_table_files_users = "xbt_files_users";
    m_table_scrape_log = "xbt_scrape_log";
    m_table_users = "xbt_users";
    m_write_db_interval = 15;

    m_fOption.addOption("announce_interval", false, m_announce_interval)
    .addOption("anonymous_announce", false, m_anonymous_announce)
    .addOption("anonymous_connect", false, m_anonymous_connect)
    .addOption("anonymous_scrape", false, m_anonymous_scrape)
    .addOption("auto_register", false, m_auto_register)
    .addOption("clean_up_interval", false, m_clean_up_interval)
    .addOption("daemon", false, m_daemon)
    .addOption("debug", false, m_debug)
    .addOption("full_scrape", false, m_full_scrape)
    .addOption("gzip_debug", false, m_gzip_debug)
    .addOption("gzip_scrape", false, m_gzip_scrape)
    .addOption("listen_ipa", false, m_listen_ipa)
    .addOption("listen_port", false, m_listen_port)
    .addOption("log_access", false, m_log_access)
    .addOption("log_announce", false, m_log_announce)
    .addOption("log_scrape", false, m_log_scrape)
    .addOption("offline_message", false, m_offline_message)
    .addOption("pid_file", false, m_pid_file)
    .addOption("read_config_interval", false, m_read_config_interval)
    .addOption("read_db_interval", false, m_read_db_interval)
    .addOption("redirect_url", false, m_redirect_url)
    .addOption("scrape_interval", false, m_scrape_interval)
    .addOption("table_announce_log", false, m_table_announce_log)
    .addOption("table_files", false, m_table_files)
    .addOption("table_files_users", false, m_table_files_users)
    .addOption("table_scrape_log", false, m_table_scrape_log)
    .addOption("table_users", false, m_table_users)
    .addOption("write_db_interval", false, m_write_db_interval);
    m_dbOption.copyOptions(m_fOption);
}

void Config::read()
{
    m_fOption.readOptions();
    m_dbOption.readOptions();
}
