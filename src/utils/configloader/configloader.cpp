#include "configloader.h"
#include "../conversion/datatypeconverter.h"

#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/validators/DTD/DTDValidator.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMDocumentType.hpp>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/dom/DOMImplementationLS.hpp>
#include <xercesc/dom/DOMNodeIterator.hpp>
#include <xercesc/dom/DOMNodeList.hpp>
#include <xercesc/dom/DOMText.hpp>
#include <xercesc/dom/DOMNamedNodeMap.hpp>

#include <xercesc/sax/HandlerBase.hpp>
#include <iostream>

using namespace xercesc;


namespace mrifit {
namespace cl {

typedef utils::DataTypeConverter DC;


unsigned int ConfigLoader::openInctances_ = 0;

ConfigLoader::ConfigLoader() throw (LoaderException):
    parser_(NULL)
{

    // track the number of active parser objects
    if (ConfigLoader::openInctances_== 0)
    {
        // Init XML Platform
        try
        {
            XMLPlatformUtils::Initialize();
        }
        catch (const XMLException& ex)
        {
            LoaderException lex("Could not initzialize XML Platform in ConfigLoader::parseXML");
            throw lex;
        }
    }

    ConfigLoader::openInctances_++;
    parser_ = new XercesDOMParser();
}


ConfigLoader::~ConfigLoader()
{
    delete parser_;

    // track the number of active parser objects
    ConfigLoader::openInctances_--;
    if (ConfigLoader::openInctances_ == 0)
    {
        XMLPlatformUtils::Terminate();
    }
}


void ConfigLoader::load() throw(LoaderException)
{
    loadConfig();
}

/// \todo: make this function exception save!!!!
void ConfigLoader::parseXML(std::string xmlfile, std::string xsdfile, XercesDOMParser* parser) throw(LoaderException)
{
    // check if there is an xml file string
    if (xmlfile == "")
    {
        throw LoaderException("No xmlfile string passed to ConfigLoader::parseXML");
    }

    // check if there is an xsd file string
    if (xsdfile == "")
    {
        throw LoaderException("No xsdfile string passed to Configloader::parseXML");
    }


    // load schema
    /// \todo check is this is necessary (seems, it is not necessary when setExternalSchemaLocation is used) -> below
    if (parser->loadGrammar(xsdfile.c_str(),Grammar::SchemaGrammarType) == NULL)
    {
        /// \todo insert filename in message
        throw LoaderException("Could not load schema file in Configloader::parseXML.");
    }


    // namespace and schema location
    std::string nsAndSchema("http://www.petrobros.net ");
    nsAndSchema += xsdfile;

    // set parser parameters

    //ErrorHandler* errHandler = (ErrorHandler*) new HandlerBase();
    ConfigLoaderErrorHandler* errHandler = new ConfigLoaderErrorHandler();
    parser->setErrorHandler(errHandler);
    parser->setValidationScheme(XercesDOMParser::Val_Always);
    parser->setLoadSchema(true);
    parser->setDoNamespaces(true);
    parser->setDoSchema(true);
    parser->setExternalSchemaLocation(nsAndSchema.c_str());
    //parser.setValidationConstraintFatal(true);
    //parser.setLoadExternalDTD(true);


    try
    {
        /// \todo might there be an exception? not well formed xml?
        parser->parse(xmlfile.c_str());

        /// \todo somehow print the specific error strings
        if (parser->getErrorCount() == 0)
                std::cout << "XML file validated against the schema successfully\n" << std::endl;
        else
        {
                std::cout <<  "XML file doesn't conform to the schema\n" << std::endl;
                std::cout << errHandler->getErrorMessage() << std::endl;
                throw(LoaderException("XML file doesn't conform to the schema"));
        }

    }
    catch (const SAXParseException &ex)
    {
        char *message = XMLString::transcode(ex.getMessage());
        std::cout << "Exception message is: \n" << message << "\n";
        XMLString::release(&message);
        /// \todo make exception save and throw loader exception
    }
    catch (const XMLException &ex)
    {
        char* message = XMLString::transcode(ex.getMessage());
        std::cout << "Exception message is: \n" << message << "\n";
        XMLString::release(&message);
        /// \todo make exception save and throw loader exception
    }
    catch (const DOMException& toCatch) {
        char* message = XMLString::transcode(toCatch.msg);
        std::cout << "Exception message is: \n" << message << "\n";
        XMLString::release(&message);
        /// \todo make exception save and throw loader exception
    }


    delete errHandler;
}



}
}
