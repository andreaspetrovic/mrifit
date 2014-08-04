#include "configbuilder.h"
#include "../../conversion/datatypeconverter.h"
#include "../loaders/datasetconfigloader.h"

#include <sstream>
#include <iostream>

// Xerces includes
#include <xercesc/dom/DOMNodeList.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/dom/DOMNode.hpp>
#include <xercesc/dom/DOMNamedNodeMap.hpp>

using namespace xercesc;

namespace mrifit {
namespace cl {

typedef utils::DataTypeConverter DC;
typedef ConfigBuilder CB;

ConfigBuilder::ConfigBuilder()
{
}


void ConfigBuilder::buildLMConfig(const DOMDocument *doc, LMConfig &lmcfg)
{

    if (isElementAvailable(doc, "tolParam"));
        lmcfg.tolParam(getElementFloat(doc,"tolParam"));

    if (isElementAvailable(doc, "tolChiSquare"))
        lmcfg.tolChiSquare(getElementFloat(doc,"tolChiSquare"));

    if (isElementAvailable(doc, "tolGrad"))
        lmcfg.tolGrad(getElementFloat(doc,"tolGrad"));

    if (isElementAvailable(doc, "acceptLMStep"))
        lmcfg.acceptLMStep(getElementFloat(doc,"acceptLMStep"));

    if (isElementAvailable(doc, "dampingLambda"))
        lmcfg.dampingLambda(getElementFloat(doc,"dampingLambda"));

    if (isElementAvailable(doc, "incFactLambda"))
        lmcfg.incFactLambda(getElementFloat(doc,"incFactLambda"));

    if (isElementAvailable(doc, "decFactLambda"))
        lmcfg.decFactLambda(getElementFloat(doc,"decFactLambda"));

    if (isElementAvailable(doc, "maxIter"))
        lmcfg.maxIter(getElementUInt(doc,"maxIter"));

}

void ConfigBuilder::buildSliceProfileConfig(const DOMDocument *doc, SliceProfileConfig &spcfg)
{
    if (isElementAvailable(doc, "sliceprofile"))
    {
        std::string str;
        str = getElementString(doc,"sliceprofile");
        std::string type = getAttributeString(doc,"sliceprofile","type");
        std::string loc = getAttributeString(doc,"sliceprofile","loc");

        spcfg.type(type);

        if (loc!="")
            spcfg.location(loc);
        else
            spcfg.data(utils::DataTypeConverter::stringToFloatVec(str));
    }


}

/// \todo write code to handle external files
void ConfigBuilder::buildMSEDataConfig(const DOMDocument *doc, MSEDataConfig &msecfg)
{

    DOMNodeList *nl = doc->getElementsByTagName(XMLString::transcode("mse"));

    if (hasAttribute(doc,"mse","nEchoes"))
        msecfg.nEchoes(getAttributeUInt(doc,"mse","nEchoes"));

    string isExternal = XMLString::transcode(nl->item(0)->getAttributes()->getNamedItem(XMLString::transcode("isExternal"))->getTextContent());
    std::cout << "Is External: " << isExternal << std::endl;
    if (isExternal == "true")
    {
        buildMSEDataConfigExternal(doc, msecfg);

    }
    else
    {

        DOMNodeList *nlfilesets = nl->item(0)->getChildNodes(); // filesets

        std::vector<std::string> msefilenames;
        for (int i=0; i< nlfilesets->getLength(); i++) // loop over filesets (attribute path, children filenames)
        {
            DOMNode *node = nlfilesets->item(i)->getAttributes()->getNamedItem(XMLString::transcode("path"));
            std::string path = XMLString::transcode(node->getTextContent()); // path
            DOMNodeList *nlfiles = nlfilesets->item(i)->getChildNodes();

            for (int k=0; k<nlfiles->getLength(); k++)
            {
                DOMNode *nodefile = nlfiles->item(k);
                std::string file = XMLString::transcode(nodefile->getTextContent()); // filenames
                std::stringstream ss;
                ss << path << "/" << file;
                msefilenames.push_back(ss.str());
            }
        }
        msecfg.filenames(msefilenames);

    }
    std::cout << "First filename: " << msecfg.filenames()[0] << std::endl;

}


void ConfigBuilder::buildMSEDataConfigExternal(const DOMDocument *doc, MSEDataConfig &msecfg)
{
    DOMNodeList *nl = doc->getElementsByTagName(XMLString::transcode("mse"));
    string externalfile = XMLString::transcode(nl->item(0)->getChildNodes()->item(0)->getChildNodes()->item(0)->getTextContent());

    DatasetConfigLoader dsCfgLoader(externalfile, "../resources/dataset.xsd");
    dsCfgLoader.load();
    DataSetConfig dscfg = dsCfgLoader.getDataSet();

    msecfg.filenames(dscfg[0]);
}


void ConfigBuilder::buildDataSetConfig(const DOMDocument *doc, DataSetConfig &dscfg)
{
    DOMNodeList *nlFilesets = doc->getElementsByTagName(XMLString::transcode("fileset"));

    for (int i=0; i < nlFilesets->getLength(); i++)
    {
        dscfg.push_back(FileSetConfig());
        DOMNamedNodeMap *nodemap = nlFilesets->item(0)->getAttributes();
        /// \todo read path
        string path = XMLString::transcode(nodemap->getNamedItem(XMLString::transcode("path"))->getTextContent());

        DOMNodeList *nlFilenames = nlFilesets->item(i)->getChildNodes();

        for(int k=0; k < nlFilenames->getLength(); k++)
        {
            DOMNode *nodefn = nlFilenames->item(k);
            string filename = XMLString::transcode(nodefn->getTextContent());
            dscfg.at(i).push_back(path + "/" + filename);
        }
    }
}



// ===============================================================================
// Helper functions

bool ConfigBuilder::isElementAvailable(const DOMDocument *doc, std::string tagname)
{
    DOMNodeList *nodes = doc->getElementsByTagName(XMLString::transcode(tagname.c_str()));

    /// \todo is this necessary or woldn't the xml validate? I think it's necessary for
    /// optional elements

    if (nodes->getLength() == 1)
        return true;
    return false;
}



float ConfigBuilder::getElementFloat(const DOMDocument *doc, std::string tagname)
{
    DOMNodeList *nodes = doc->getElementsByTagName(XMLString::transcode(tagname.c_str()));
    std::string str = XMLString::transcode(nodes->item(0)->getTextContent());
    return DC::stringToFloat(str);
}


unsigned int ConfigBuilder::getElementUInt(const DOMDocument *doc, std::string tagname)
{
    DOMNodeList *nodes = doc->getElementsByTagName(XMLString::transcode(tagname.c_str()));
    std::string str = XMLString::transcode(nodes->item(0)->getTextContent());
    return DC::stringToUInt(str);
}

std::string ConfigBuilder::getElementString(const DOMDocument *doc, std::string tagname)
{
    DOMNodeList *nodes = doc->getElementsByTagName(XMLString::transcode(tagname.c_str()));
    std::string str = XMLString::transcode(nodes->item(0)->getTextContent());
    return str;
}

bool ConfigBuilder::hasAttribute(const xercesc::DOMDocument *doc,
                                const std::string &tagname,
                                const std::string &attrname)
{
    DOMNodeList *nodes = doc->getElementsByTagName(XMLString::transcode(tagname.c_str()));
    DOMNamedNodeMap *nodemap = nodes->item(0)->getAttributes();
    DOMNode *attrnode = nodemap->getNamedItem(XMLString::transcode(attrname.c_str()));

    if (attrnode != NULL)
        return true;
    return false;
}


std::string ConfigBuilder::getAttributeString(const xercesc::DOMDocument *doc,
                                             const std::string &tagname,
                                             const std::string &attrname)
{
    DOMNodeList *nodes = doc->getElementsByTagName(XMLString::transcode(tagname.c_str()));
    DOMNamedNodeMap *nodemap = nodes->item(0)->getAttributes();
    DOMNode *node = nodemap->getNamedItem(XMLString::transcode(attrname.c_str()));
    std::string str = XMLString::transcode(node->getTextContent());
    return str;
}

unsigned int ConfigBuilder::getAttributeUInt(const DOMDocument *doc, const std::string &tagname, const std::string &attrname)
{
    return DC::stringToUInt(getAttributeString(doc, tagname, attrname));
}




}
}
