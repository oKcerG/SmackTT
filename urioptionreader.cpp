#include "urioptionreader.h"
#include "utils.h"
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/foreach.hpp>

#define foreach BOOST_FOREACH

using namespace boost;
using namespace std;

UriOptionReader::UriOptionReader(const string& uri) : m_uri(uri)
{
    //ctor
}

void UriOptionReader::doReadOptions()
{

    string key, value;
    bool keyFound = false;
    size_t l = m_uri.length();
    for (size_t i = 0; i < l; i++)
    {
        char c = m_uri[i];
        if (!keyFound)
        {
            if (c == '=')
                keyFound = true;
            else
                key += c;
        }
        else
        {
            if (c == '&')
            {
                m_values[key] = value;//utils::decodeUri(value);
                key.clear();
                value.clear();
                keyFound = false;
            }
            else
                value += c;
        }
    }
}
