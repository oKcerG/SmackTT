#include "bencodedstring.h"
#include <sstream>

BencodedString::BencodedString(const std::string& data) : m_data(data)
{
}

const std::string& BencodedString::str() const
{
    return m_data;
}

BencodedString& BencodedString::operator<<(int i)
{
    std::ostringstream stream;
    stream << i;
    m_data += "i" + stream.str() + "e";
    return *this;
}

BencodedString& BencodedString::operator<<(const std::string& str)
{
    std::ostringstream stream;
    stream << str.size();
    m_data += stream.str() + ":" + str;
    return *this;
}

BencodedString& BencodedString::operator<<(const manipulator& manip)
{
    return manip(*this);
}

BencodedString& BencodedString::beginDic(BencodedString& bstr)
{
    bstr.m_data += 'd';
    return bstr;
}

BencodedString& BencodedString::beginList(BencodedString& bstr)
{
    bstr.m_data += 'l';
    return bstr;
}

BencodedString& BencodedString::end(BencodedString& bstr) //end a list or a dic
{
    bstr.m_data += 'e';
    return bstr;
}

