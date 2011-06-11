#ifndef OPTION_H
#define OPTION_H

#include <string>
#include <sstream>
#include <iostream>
class Option
{

public:
    Option(const std::string& name, bool mandatory);

    bool mandatory() const;
    const std::string& name() const;

    void operator<<(const std::string& str);

private:
    virtual void setValue(const std::string& str) = 0;
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

private:
    void setValue(const std::string& str)
    {
        std::istringstream iss(str);
        iss >> m_value;
    }
    T& m_value;
};

template <>
void OptionImpl<std::string>::setValue(const std::string& str);

#endif // OPTION_H
