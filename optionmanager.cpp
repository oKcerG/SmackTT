#include "optionmanager.h"
#include <stdexcept>

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
    for (auto& reader : m_readers)
        reader.readOptions(values);

    /*typedef std::pair<std::string, std::string> string_pair;
    foreach (const string_pair& pair, values)
    {
        std::cout.width(15);
        std::cout << pair.first << " : " << pair.second << std::endl;
    }*/

    auto vend = values.end();
    for (auto& option : m_options)
    {
        auto vit = values.find(option.name());
        if (vit != vend)
            option << vit->second;
        else if (option.mandatory())
            throw std::runtime_error("Option not found : " +option.name());
    }

}
