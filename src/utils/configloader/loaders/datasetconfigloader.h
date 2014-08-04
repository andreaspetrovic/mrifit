#ifndef DATASETCONFIGLOADER_H
#define DATASETCONFIGLOADER_H

#include "../configloader.h"
#include "../configs/datasetconfig.h"

using std::string;
using std::vector;

namespace mrifit {
namespace cl {



/*!
 * \brief Configuration loader for a dataset (i.e. several filesets consisting of several filenames)
 * \ingroup group_configloader
 */
class DatasetConfigLoader : public ConfigLoader
{
public:
    /*!
     * \brief DatasetConfigLoader
     * \param filename xml config filename
     * \param schemafilename xsd schema filename
     */
    DatasetConfigLoader(std::string filename, std::string schemafilename) throw(LoaderException);
    virtual ~DatasetConfigLoader();
    /*!
     * \brief returns the loaded dataset
     * \todo rather return it as reference????
     * \return
     */
    DataSetConfig getDataSet();
private:
    /*!
     * \brief Implemntation of loadConfig() interface.
     */
    void loadConfig() throw(LoaderException);
    string filename_;
    string schemafilename_;
    DataSetConfig ds_;
};


}
}
#endif // DATASETCONFIGLOADER_H
