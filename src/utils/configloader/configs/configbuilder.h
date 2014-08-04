#ifndef CONFIGBUILDER_H
#define CONFIGBUILDER_H

#include <string>
#include <xercesc/dom/DOMDocument.hpp>

#include "sliceprofileconfig.h"
#include "lmconfig.h"
#include "msedataconfig.h"
#include "datasetconfig.h"


using xercesc::DOMDocument;


namespace mrifit {
namespace cl {

/*!
 * \brief The ConfigBuilder class
 * \ingroup group_configloader
 */
class ConfigBuilder
{
public:
    ConfigBuilder();
    static void buildSliceProfileConfig(const DOMDocument *doc, SliceProfileConfig &spcfg);
    static void buildLMConfig(const DOMDocument *doc, LMConfig &lmcfg);
    static void buildMSEDataConfig(const DOMDocument *doc, MSEDataConfig &msecfg);
    static void buildDataSetConfig(const DOMDocument *doc, DataSetConfig &dscfg);

    /// \todo rename to hasElement
    static bool isElementAvailable(const DOMDocument *doc, std::string tagname);
    static float getElementFloat(const DOMDocument *doc, std::string tagname);
    static unsigned int getElementUInt(const DOMDocument *doc, std::string tagname);
    static std::string getElementString(const DOMDocument *doc, std::string tagname);

    static bool hasAttribute(const DOMDocument *doc, const std::string &tagname, const std::string &attrname);
    static std::string getAttributeString(const DOMDocument *doc, const std::string &tagname, const std::string &attrname);
    static unsigned int getAttributeUInt(const DOMDocument *doc, const std::string &tagname, const std::string &attrname);
private:
    static void buildMSEDataConfigExternal(const DOMDocument *doc, MSEDataConfig &msecfg);
};



}
}

#endif // CONFIGBUILDER_H
