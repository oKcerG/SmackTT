#ifndef OPTION_H
#define OPTION_H

#include <string>
#include <sstream>

#include <boost/shared_ptr.hpp>

class Option
{

public:
    Option(const std::string& name, bool mandatory) : m_name(name), m_mandatory(mandatory) {}

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


template <typename T>
class OptionImpl : public Option
{
public:
    OptionImpl(const std::string& name, T& value) : Option(name, true), m_value(value)
    {

    }

    OptionImpl(const std::string& name, T& value, const T& default_value) : Option(name, false), m_value(value)
    {
        m_value = default_value;
    }

    void operator<<(const std::string& str)
    {
        std::istringstream iss(str);
        iss >> m_value;
    }

private:
    T& m_value;
};

template <>
void OptionImpl<std::string>::operator<<(const std::string& str);

#endif // OPTION_H
