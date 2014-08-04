#ifndef FITCONFIGLOADER_H
#define FITCONFIGLOADER_H

#include <string>
#include <xercesc/parsers/XercesDOMParser.hpp>

#include "loaderexception.h"
#include "configloadererrorhandler.h"

using namespace xercesc;

namespace mrifit {
namespace cl {


/*!
 * \brief The ConfigLoader class, base class to all xml-config file loaders
 * \ingroup group_configloader
 */
class ConfigLoader
{
public:
    ConfigLoader() throw (LoaderException);
    virtual ~ConfigLoader();    
    /*!
     * \brief Common interface to load a configuration file. Calls the loadConfig function
    which has to be implemented in the derived class.
     */
    void load() throw(LoaderException);
protected:
    /*!
     * \brief Parses the xml file and validates it against the given xsd schema file.
     * \param xmlfile <path>/<file>.xml (configuration file)
     * \param xsdfile <path>/<file>.xsd (schema to validate against)
     * \param parser instance of a DOMParser
     * \throw LoaderException Throws if something wasn't successfull (loading xml, xsd, validation, well-formedness)
     */
    void parseXML(std::string xmlfile, std::string xsdfile, xercesc::XercesDOMParser* parser) throw(LoaderException);

    /*!
     * \brief instance of DOMParser
     */
    xercesc::XercesDOMParser *parser_;

    /// counts the open configloader instances (necessary for the XML platform).
    static unsigned int openInctances_;

private:
    /*!
     * \brief Actually does the job of extracting the config values from the DOMDocument.
     * Has to be implemented in the derived class.
     */
    virtual void loadConfig() throw(LoaderException) = 0;    
};



}
}

#endif // FITCONFIGLOADER_H
