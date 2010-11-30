#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include "fileoptionreader.h"
#include "databaseoptionreader.h"

class Database;

class Config
{
    public:
        Config(Database& database);
        void read();
        int announce_interval() const {return m_announce_interval;}
        bool anonymous_connect() const {return m_anonymous_connect;}
        bool anonymous_announce() const {return m_anonymous_announce;}
        bool anonymous_scrape() const {return m_anonymous_scrape;}
        bool auto_register() const {return m_auto_register;}
        int clean_up_interval() const {return m_clean_up_interval;}
        bool daemon() const {return m_daemon;}
        bool debug() const {return m_debug;}
        bool full_scrape() const {return m_full_scrape;}
        bool gzip_debug() const {return m_gzip_debug;}
        bool gzip_scrape() const {return m_gzip_scrape;}
        std::string listen_ipa() const {return m_listen_ipa;}
        int listen_port() const {return m_listen_port;}
        bool log_access() const {return m_log_access;}
        bool log_announce() const {return m_log_announce;}
        bool log_scrape() const {return m_log_scrape;}
        std::string offline_message() const {return m_offline_message;}
        std::string pid_file() const {return m_pid_file;}
        int read_config_interval() const {return m_read_config_interval;}
        int read_db_interval() const {return m_read_db_interval;}
        std::string redirect_url() const {return m_redirect_url;}
        int scrape_interval() const {return m_scrape_interval;}
        std::string table_announce_log() const {return m_table_announce_log;}
        std::string table_files() const {return m_table_files;}
        std::string table_files_users() const {return m_table_files_users;}
        std::string table_scrape_log() const {return m_table_scrape_log;}
        std::string table_users() const {return m_table_users;}
        int write_db_interval() const {return m_write_db_interval;}


    protected:
    private:
        FileOptionReader m_fOption;
        DatabaseOptionReader m_dbOption;
        int m_announce_interval;
        bool m_anonymous_connect;
        bool m_anonymous_announce;
        bool m_anonymous_scrape;
        bool m_auto_register;
        int m_clean_up_interval;
        bool m_daemon;
        bool m_debug;
        bool m_full_scrape;
        bool m_gzip_debug;
        bool m_gzip_scrape;
        std::string m_listen_ipa;
        int m_listen_port;
        bool m_log_access;
        bool m_log_announce;
        bool m_log_scrape;
        std::string m_offline_message;
        std::string m_pid_file;
        int m_read_config_interval;
        int m_read_db_interval;
        std::string m_redirect_url;
        int m_scrape_interval;
        std::string m_table_announce_log;
        std::string m_table_files;
        std::string m_table_files_users;
        std::string m_table_scrape_log;
        std::string m_table_users;
        int m_write_db_interval;
};

#endif // CONFIG_H
