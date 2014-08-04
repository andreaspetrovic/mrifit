#include "datatypeconverter.h"

#include <sstream>
#include <boost/tokenizer.hpp>

namespace mrifit {
namespace utils {


DataTypeConverter::DataTypeConverter()
{
}

float DataTypeConverter::stringToFloat(const std::string &str)
{
    std::stringstream ss;
    ss << str;
    float f;
    ss >> f;
    return f;
}

unsigned int DataTypeConverter::stringToUInt(const std::string &str)
{
    std::stringstream ss;
    ss << str;
    unsigned int i;
    ss >> i;
    return i;
}


std::vector<float> DataTypeConverter::stringToFloatVec(std::string& str, const char* seperator)
{

    boost::char_separator<char> sep(seperator);
    typedef boost::tokenizer<boost::char_separator<char> > septokenizer;

    septokenizer tok(str,sep);

    std::vector<float> vec;
    for(septokenizer::iterator beg=tok.begin(); beg!=tok.end();++beg){
           std::cout << *beg << "\n";
           vec.push_back(DataTypeConverter::stringToFloat(*beg));
    }
    return vec;
}


}
}
