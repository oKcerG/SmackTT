#ifndef URIOPTIONREADER_H
#define URIOPTIONREADER_H

/*
#include "optionreader.h"
#include <string>

class UriOptionReader : public OptionReader
{
    public:
        UriOptionReader(const std::string& uri);

    private:
        void doReadOptions(std::map<std::string, std::string>& values);
        std::string m_uri;
};
*/

#include "istreamoptionreader.h"
#include "utils.h"

inline void decode(std::string& text)
{
    text = utils::decodeUri(text);
}
typedef IStreamOptionReader<'=','&',doNothing,decode,alwaysFalse> UriOptionReader;

#endif // URIOPTIONREADER_H
