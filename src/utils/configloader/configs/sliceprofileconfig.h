#ifndef SLICEPROFILECONFIG_H
#define SLICEPROFILECONFIG_H

#include <string>
#include <vector>

namespace mrifit {
namespace cl {


/*!
 * \brief SliceProfileConfig stores a data for the slice profile.
 * \ingroup group_configloader
 */
class SliceProfileConfig
{
public:
    SliceProfileConfig();

    /// This determines the datatype, i.e. how the data shall be interpreted.
    enum TYPE {SLICE_PROFILE_ABS /// The given data is the absolute value of the slice profile
    };

    void type(TYPE t);
    void type(std::string t);
    TYPE type();
    void data(const std::vector<float> &d);
    std::vector<float> &data();
    /// If the location set is not equal to "" the isExternalFile flag is set to true!
    void location(const std::string &s);
    std::string &location();
    void isExternalFile(bool b);
    bool isExternalFile();

private:
    TYPE type_;
    std::vector<float> data_;
    std::string location_;
    bool isExternalFile_;
};

}
}

#endif // SLICEPROFILECONFIG_H
