#ifndef T2FitGFConfigLoader_H
#define T2FitGFConfigLoader_H


#include "../configloader.h"
#include "../configs/lmconfig.h"
#include "../configs/sliceprofileconfig.h"
#include "../configs/msedataconfig.h"


namespace mrifit {
namespace cl {


/*!
 * \brief Class to load the configuration parameters for a generating functions T2 fit.
 * \param filename xml config file
 * \ingroup group_configloader
 */
class T2FitGFConfigLoader : public ConfigLoader
{
public:
    /*!
     * \brief T2FitGFConfigLoader
     * \param filename Configuration xml file.
     */
    explicit T2FitGFConfigLoader(std::string filename) throw (LoaderException);

    /*!
     * \brief T2FitGFConfigLoader
     * \param filename Configuration xml file.
     * \param schemafilename XSD schema file to validate against.
     */
    T2FitGFConfigLoader(std::string filename, std::string schemafilename) throw (LoaderException);
    virtual ~T2FitGFConfigLoader();

    /*!
     * \brief Returns the loaded config object for the Levenberg-Marquardt optimizer.
     * \return
     */
    LMConfig& getLMConfig();

private:
    /*!
     * \brief Implemntation of loadConfig() interface.
     */
    virtual void loadConfig() throw(LoaderException);
    std::string filename_;
    std::string schemafilename_;

    /// default value for xsd schema file.
    static const std::string XSDFILENAME_;

    /// Individual config objects.
    LMConfig lmcfg_;
    SliceProfileConfig spcfg_;
    MSEDataConfig msecfg_;
};

}
}


#endif // T2FitGFConfigLoader_H
