#ifndef DATASETCONFIG_H
#define DATASETCONFIG_H

#include <string>
#include <vector>
using std::string;
using std::vector;

/*!
 * \typedef FileSetConfig
 * \brief A vector of <path>/<filename>'s
 * \ingroup group_configloader
 */
typedef vector<string> FileSetConfig;

/*!
 * \typedef DataSetConfig
 * \brief A vector of FileSetConfigs
 * \ingroup group_configloader
 */
typedef vector<FileSetConfig> DataSetConfig;


class DataSetConfigObj
{
public:
    DataSetConfigObj() :
        dscfg_(DataSetConfig())
    {}
    virtual ~DataSetConfigObj() {}

protected:
    DataSetConfig dscfg_;
    void dataSet(DataSetConfig dscfg)
    {
        dscfg_ = dscfg;
    }

    DataSetConfig dscfg()
    {
        return dscfg_;
    }

};

#endif // DATASETCONFIG_H
