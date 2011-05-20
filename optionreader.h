#ifndef OPTIONREADER_H
#define OPTIONREADER_H

#include <map>
#include <string>

class OptionReader
{
public:
    OptionReader();
    virtual ~OptionReader();
    void readOptions(std::map<std::string, std::string>& values);

private:
    virtual void doReadOptions(std::map<std::string, std::string>& values) = 0;
};

#endif // OPTIONREADER_H
