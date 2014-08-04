#include "sliceprofileconfig.h"

namespace mrifit {
namespace cl {

SliceProfileConfig::SliceProfileConfig() :
    type_(SLICE_PROFILE_ABS),
    location_(""),
    data_(std::vector<float>(1.0)),
    isExternalFile_(false)
{
}

void SliceProfileConfig::type(SliceProfileConfig::TYPE t)
{
    type_ = t;
}

void SliceProfileConfig::type(std::string t)
{
    if (t == "slice_abs")
        type_ = SliceProfileConfig::SLICE_PROFILE_ABS;
}



SliceProfileConfig::TYPE SliceProfileConfig::type()
{
    return type_;
}

void SliceProfileConfig::data(const std::vector<float> &d)
{
    data_ = d;
}

std::vector<float> &SliceProfileConfig::data()
{
    return data_;
}

void SliceProfileConfig::location(const std::string &s)
{
    location_ = s;
    if (location_ != "")
        isExternalFile_ = true;
    else
        isExternalFile_ = false;
}

std::string &SliceProfileConfig::location()
{
    return location_;
}

void SliceProfileConfig::isExternalFile(bool b)
{
    isExternalFile_ = b;
}

bool SliceProfileConfig::isExternalFile()
{
    return isExternalFile_;
}


}
}
