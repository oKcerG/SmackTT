#ifndef OPTIONREADER_H
#define OPTIONREADER_H

#include <map>
#include <string>

class OptionReader
{
public:
    OptionReader();
    virtual ~OptionReader() = 0;
    const std::map<std::string, std::string>& values() const;
    void readOptions();

protected:
    std::map<std::string, std::string> m_values;

private:
    virtual void doReadOptions() = 0;
};

#endif // OPTIONREADER_H
