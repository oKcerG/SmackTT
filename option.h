#ifndef OPTION_H
#define OPTION_H

#include <string>
#include <sstream>

#include <iostream>

class OptionBase
{

public:
    OptionBase(const std::string& name, bool mandatory) : m_name(name), m_mandatory(mandatory) {}

    bool mandatory() const
    {
        return m_mandatory;
    }
    const std::string& name() const
    {
        return m_name;
    }

    virtual void operator<<(const std::string& str) = 0;

private:
    std::string m_name;
    bool m_mandatory;

};


template <typename T> class Option : public OptionBase
{
public:
    Option(const std::string& name, bool mandatory, T& value) : OptionBase(name, mandatory), m_value(value) {}

    void operator<<(const std::string& str)
    {
        std::istringstream stream(str);
        stream >> m_value;
    }

private:
    T& m_value;
};

template <> class Option<std::string> : public OptionBase
{
public:
    Option(const std::string& name, bool mandatory, std::string& value) : OptionBase(name, mandatory), m_value(value) {}

    void operator<<(const std::string& str)
    {
        m_value = str;
    }

private:
    std::string& m_value;
};


#endif // OPTION_H
