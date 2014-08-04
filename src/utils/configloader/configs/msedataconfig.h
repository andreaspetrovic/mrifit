#ifndef MSEDATACONFIG_H
#define MSEDATACONFIG_H

#include <string>
#include <vector>

namespace mrifit {
namespace cl {

using std::vector;
using std::string;


/*!
 * \brief MSEDataConfig stores a set of files for multi echo data. Additionally it can
 * store the number of echoes.
 * \ingroup group_configloader
 */
class MSEDataConfig
{
public:
    MSEDataConfig();
    void nEchoes(unsigned int i);
    unsigned int nEchoes();
    void filenames(vector<string> f);
    vector<string> filenames();

private:
    unsigned int nEchoes_;
    vector<string> filenames_;
};

}
}

#endif // MSEDATACONFIG_H
