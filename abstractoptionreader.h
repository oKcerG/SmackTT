#ifndef ABSTRACTOPTIONREADER_H
#define ABSTRACTOPTIONREADER_H

#include <map>
#include <vector>
#include <string>
#include "option.h"
#include <iostream>
#include <exception>
#include <boost/shared_ptr.hpp>

typedef boost::shared_ptr<OptionBase> optPointer;


class AbstractOptionReader
{
public:
    class OptionNotFound : public std::exception
    {
    public:
        OptionNotFound(const std::string& name) throw(): m_name(name) {}
        ~OptionNotFound() throw() {}
        const char *what(void) const throw()
        {
            std::string error = "Mandatory option not found : " + m_name;
            return error.c_str();
        }
        const std::string& name()
        {
            return m_name;
        }

    protected:
        std::string m_name;

    };

    AbstractOptionReader();
    AbstractOptionReader& addOption(optPointer option);
    template <typename T> AbstractOptionReader& addOption(const std::string& name, bool mandatory, T& value)
    {
        return addOption(optPointer(new Option<T>(name, mandatory, value)));
    };
    void copyOptions(const AbstractOptionReader& other);
    void readOptions();

protected:
    virtual void readValues() = 0;

    std::map <std::string, std::string> m_values;
    std::vector <optPointer> m_options;
private:
};

#endif // ABSTRACTOPTIONREADER_H
