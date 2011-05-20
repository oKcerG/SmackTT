#include "optionmanager.h"
#include <boost/foreach.hpp>
#include <stdexcept>

#define foreach BOOST_FOREACH

OptionManager::OptionManager()
{

}


OptionManager::OptionManager(OptionReader* reader)
{
    addReader(reader);
}


void OptionManager::addReader(OptionReader* reader)
{
    m_readers.push_back(reader);
}


OptionManager& OptionManager::addOption(Option* option)
{
    m_options.push_back(option);
    return *this;
}


void OptionManager::readOptions()
{
    std::map<std::string, std::string> values;
    foreach(OptionReader& reader, m_readers)
        reader.readOptions(values);

    std::map<std::string, std::string>::const_iterator vit, vend = values.end();
    foreach (Option& option, m_options)
    {
        if ((vit = values.find(option.name())) != vend)
            option << vit->second;
        else if (option.mandatory())
            throw std::runtime_error("Option not found : " +option.name());
    }

}
