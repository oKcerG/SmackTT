#ifndef DATABASECONFIG_H
#define DATABASECONFIG_H

#include <string>

class DatabaseConfig
{
public:
    DatabaseConfig();
    const std::string& host() const
    {
        return m_host;
    }
    const std::string& user() const
    {
        return m_user;
    }
    const std::string& password() const
    {
        return m_password;
    }
    const std::string& database() const
    {
        return m_database;
    }

private:
    DatabaseConfig(const DatabaseConfig&);
    std::string m_host;
    std::string m_user;
    std::string m_password;
    std::string m_database;
};

#endif // DATABASECONFIG_H
