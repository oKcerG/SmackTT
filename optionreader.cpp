#include "optionreader.h"

OptionReader::OptionReader()
{

}


OptionReader::~OptionReader()
{

}


void OptionReader::readOptions(std::map<std::string, std::string>& values)
{
    doReadOptions(values);
}
