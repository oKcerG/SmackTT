#include "abstractoptionreader.h"
#include <boost/foreach.hpp>
#include <iostream>

#define foreach BOOST_FOREACH

AbstractOptionReader::AbstractOptionReader()
{
    //ctor
}


void AbstractOptionReader::copyOptions(const AbstractOptionReader& other) // :(
{
    m_options = other.m_options;
}

AbstractOptionReader& AbstractOptionReader::addOption(optPointer option)
{
    m_options.push_back(option);
    return *this;
}

void AbstractOptionReader::readOptions()
{
    readValues();
    std::map<std::string, std::string>::iterator vit, vend = m_values.end();

    foreach (optPointer option, m_options)
    {
        if ((vit = m_values.find(option->name())) != vend)
            *option << vit->second;
        else if (option->mandatory())
            throw OptionNotFound(option->name());
    }
}
