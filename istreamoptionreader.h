#ifndef ISTREAMOPTIONREADER_H
#define ISTREAMOPTIONREADER_H

#include "optionreader.h"
#include <istream>
#include <iostream>

inline void doNothing(std::string& /*string*/) {}
inline bool alwaysFalse(const std::string& /*string*/) {return false;}

template <
char delim1,
char delim2,
void (*func1)(std::string&),
void (*func2)(std::string&),
bool (*pred)(const std::string&) = alwaysFalse
>
class IStreamOptionReader : public OptionReader
{
public:
    IStreamOptionReader(std::istream& stream) : m_stream(stream) {}
private:
    void doReadOptions(std::map<std::string, std::string>& values)
    {
        std::string key, value;
        bool skip = false;
        while (m_stream.good())
        {
            if (key.empty())
            {
                std::getline(m_stream, key, delim1);
                func1(key);
                if (pred(key))
                    skip = true;
            }
            else
            {
                std::getline(m_stream, value, delim2);
                if (!skip)
                {
                    func2(value);
                    values[key] = value;
                }
                skip = false;
                key.clear();
            }
        }
    }
    std::istream& m_stream;
};

#endif // ISTREAMOPTIONREADER_H
