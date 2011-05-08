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
    //*
    typedef iterator_range<string::const_iterator> stringItRange;
    typedef vector<stringItRange> splitVector;
    splitVector splitVec;
    split(splitVec, m_uri, is_any_of("&="));
    std::string key;
    foreach (const stringItRange& it, splitVec)
    {
        if (key.empty())
        {
            key = copy_range<std::string>(it);
        }
        else
        {
            m_values[key] = copy_range<std::string>(it);//utils::decodeUri(copy_range<std::string>(it));
            key.clear();
        }
    }
    //*/
    /*
    typedef split_iterator<string::iterator> sIt;
    for (sIt it = make_split_iterator(m_uri, first_finder("=&", all());
             it != sIt();
             ++it)
             {
                 cout << "#########################\n" << copy_range<std::string>(*it) << endl;
             }
    */
}
