#ifndef OPTIONMANAGER_H
#define OPTIONMANAGER_H

#include <boost/ptr_container/ptr_vector.hpp>
#include <string>
#include "option.h"
#include "optionreader.h"

class OptionManager
{
public:
    OptionManager();
    OptionManager(OptionReader* reader);
    void readOptions();
    void addReader(OptionReader* reader);
    template <typename T>
    OptionManager& addOption(const std::string& name, T& value)
    {
        return addOption(new OptionImpl<T>(name, value));
    }
    template <typename T, typename U>
    OptionManager& addOption(const std::string& name, T& value, const U& default_value)
    {
        return addOption(new OptionImpl<T>(name, value, default_value));
    }

private:
    OptionManager& addOption(Option* option);
    boost::ptr_vector<Option> m_options;
    boost::ptr_vector<OptionReader> m_readers;
};

#endif // OPTIONMANAGER_H
