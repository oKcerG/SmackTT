#ifndef BENCODEDDATA_H
#define BENCODEDDATA_H

#include <boost/any.hpp>
#include <boost/shared_ptr.hpp>
#include <vector>

class BencodedData
{
    public:
    typedef boost::shared_ptr<BencodedData> pointer;
        BencodedData();
    protected:
    private:
        std::vector<pointer> m_vec;
};

#endif // BENCODEDDATA_H
