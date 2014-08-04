#include "datasetconfigloader.h"
#include "../configs/configbuilder.h"

using namespace xercesc;

namespace mrifit {
namespace cl {

DatasetConfigLoader::DatasetConfigLoader(string filename, string schemafilename) throw(LoaderException):
    ConfigLoader(),
    filename_(filename),
    schemafilename_(schemafilename),
    ds_(DataSetConfig())
{
}

DatasetConfigLoader::~DatasetConfigLoader()
{

}

void DatasetConfigLoader::loadConfig() throw(LoaderException)
{
    parser_->setIncludeIgnorableWhitespace(false);
    try
    {
        this->parseXML(filename_,schemafilename_,parser_);
    }
    catch (LoaderException &lex)
    {
        throw lex;
    }

    /// \todo this has to be moved to builder class to be reused
    DOMDocument *doc = parser_->getDocument();

    ConfigBuilder::buildDataSetConfig(doc, ds_);
}

DataSetConfig DatasetConfigLoader::getDataSet()
{
    return ds_;
}

}
}
