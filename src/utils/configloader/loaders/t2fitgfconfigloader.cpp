#include "t2fitgfconfigloader.h"
#include "../configs/configbuilder.h"
#include <iostream>





using namespace xercesc;

namespace mrifit {
namespace cl {


const std::string T2FitGFConfigLoader::XSDFILENAME_= "../resources/t2fit.xsd";


T2FitGFConfigLoader::T2FitGFConfigLoader(std::string filename) throw (LoaderException) :
    ConfigLoader(),
    filename_(filename),
    schemafilename_(T2FitGFConfigLoader::XSDFILENAME_),
    lmcfg_(LMConfig()),
    spcfg_(SliceProfileConfig()),
    msecfg_(MSEDataConfig())
{
}

T2FitGFConfigLoader::T2FitGFConfigLoader(std::string filename, std::string schemafilename) throw (LoaderException):
    ConfigLoader(),
    filename_(filename),
    schemafilename_(schemafilename),
    lmcfg_(LMConfig()),
    spcfg_(SliceProfileConfig()),
    msecfg_(MSEDataConfig())
{

}


void T2FitGFConfigLoader::loadConfig() throw(LoaderException)
{
    parser_->setIncludeIgnorableWhitespace(false);
    // this checks if the xml is well formed and valid
    try
    {
        this->parseXML(filename_,schemafilename_,parser_);
    }
    catch (LoaderException &lex)
    {
        throw lex;
    }

    DOMDocument *doc = parser_->getDocument();

    // write values to lenvenberg marquardt config object ==============================
    ConfigBuilder::buildLMConfig(doc, lmcfg_);

    // write values to slice profile config ===============================================
    ConfigBuilder::buildSliceProfileConfig(doc, spcfg_);

    // write values to mse config object ====================================================
    ConfigBuilder::buildMSEDataConfig(doc, msecfg_);

    std::cout << "NEchoes: " << msecfg_.nEchoes() << std::endl;
    std::cout << "LengthDATA: " << msecfg_.filenames().size() << std::endl;
}


T2FitGFConfigLoader::~T2FitGFConfigLoader()
{
}

LMConfig &T2FitGFConfigLoader::getLMConfig()
{
    return lmcfg_;
}


}
}
