#include "optionreader.h"

OptionReader::OptionReader()
{

}


OptionReader::~OptionReader()
{

}


const std::map<std::string, std::string>& OptionReader::values() const
{
    return m_values;
}


void OptionReader::readOptions()
{
    doReadOptions();
}
