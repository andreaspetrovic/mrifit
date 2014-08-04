#include "msedataconfig.h"

namespace mrifit {
namespace cl {


MSEDataConfig::MSEDataConfig() :
    nEchoes_(0),
    filenames_(vector<string>())
{
}

void MSEDataConfig::filenames(vector<string> f)
{
    filenames_ = f;
}

vector<string> MSEDataConfig::filenames()
{
    return filenames_;
}

void MSEDataConfig::nEchoes(unsigned int i)
{
    nEchoes_ = i;
}

unsigned int MSEDataConfig::nEchoes()
{
    return nEchoes_;
}

}
}
