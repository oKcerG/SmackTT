#ifndef BENCODEDSTRING_H
#define BENCODEDSTRING_H

#include <string>
#include <map>
#include <boost/variant.hpp>

class BencodedString
{
public:
    typedef BencodedString& manipulator(BencodedString&);

    BencodedString(const std::string& data = std::string());

    const std::string& str() const;

    BencodedString& operator<<(int i);
    BencodedString& operator<<(const std::string& str);
    BencodedString& operator<<(const manipulator& manip);

    static BencodedString& beginDic(BencodedString& bstr);
    static BencodedString& beginList(BencodedString& bstr);
    static BencodedString& end(BencodedString& bstr);

private:
    std::string m_data;
};

#endif // BENCODEDSTRING_H
