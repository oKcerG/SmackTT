#ifndef BENCODEDSTRING_H
#define BENCODEDSTRING_H

#include <string>
#include <map>
#include <boost/variant.hpp>

class BencodedString
{
public:
    typedef BencodedString& manipulator (BencodedString&);

    BencodedString(std::string data = std::string());

    std::string str() const;

    BencodedString& operator<<(int i);
    BencodedString& operator<<(std::string str);
    BencodedString& operator<<(manipulator manip);

    static BencodedString& beginDic(BencodedString& bstr);
    static BencodedString& beginList(BencodedString& bstr);
    static BencodedString& end(BencodedString& bstr);

private:
    std::string m_data;
};

#endif // BENCODEDSTRING_H
