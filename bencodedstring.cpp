#include "bencodedstring.h"


BencodedString::BencodedString()
{
}

std::string BencodedString::str() const
{
    return m_stream.str();
}

BencodedString& BencodedString::operator<<(int i)
{
    m_stream << 'i' << i << 'e';
    return *this;
}

BencodedString& BencodedString::operator<<(const std::string& str)
{
    m_stream << str.size() << ':' << str;
    return *this;
}

BencodedString& BencodedString::operator<<(const manipulator& manip)
{
    return manip(*this);
}

BencodedString& BencodedString::beginDic(BencodedString& bstr)
{
    bstr.m_stream << 'd';
    return bstr;
}

BencodedString& BencodedString::beginList(BencodedString& bstr)
{
    bstr.m_stream << 'l';
    return bstr;
}

BencodedString& BencodedString::end(BencodedString& bstr) //end a list or a dic
{
    bstr.m_stream << 'e';
    return bstr;
}

