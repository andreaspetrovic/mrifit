#ifndef DATATYPECONVERTER_H
#define DATATYPECONVERTER_H

#include <string>
#include <vector>

namespace mrifit {
namespace utils {


class DataTypeConverter
{
public:
    DataTypeConverter();
    static float stringToFloat(const std::string& str);
    static unsigned int stringToUInt(const std::string& str);
    static std::vector<float> stringToFloatVec(std::string& str, const char* seperator = ",");
};


}
}
#endif // DATATYPECONVERTER_H

