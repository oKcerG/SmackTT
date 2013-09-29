#ifndef BENCODEDSTRING_H
#define BENCODEDSTRING_H

#include <sstream>
#include <string>

class BencodedString
{
public:
    typedef BencodedString& manipulator(BencodedString&);

    BencodedString();

    std::string str() const;
    void clear();

    BencodedString& operator<<(int i);
    BencodedString& operator<<(const std::string& str);
    BencodedString& operator<<(const manipulator& manip);

    static BencodedString& beginDic(BencodedString& bstr);
    static BencodedString& beginList(BencodedString& bstr);
    static BencodedString& end(BencodedString& bstr);

private:
    std::ostringstream m_stream;
};

#endif // BENCODEDSTRING_H
