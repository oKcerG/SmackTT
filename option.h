#ifndef OPTION_H
#define OPTION_H

#include <string>
#include <sstream>
#include <iostream>

template <typename T>
void from_string(T& value, const std::string& str);

class Option
{

public:
    Option(const std::string& name, bool mandatory);
    virtual ~Option(){}

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
        from_string(m_value, str);
    }
    T& m_value;
};

template <typename T>
void from_string(T& value, const std::string& str)
{
    std::istringstream iss(str);
    iss >> value;
}

template <>
void from_string<std::string>(std::string& value, const std::string& str);

#endif // OPTION_H
