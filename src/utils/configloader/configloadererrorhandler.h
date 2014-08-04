#ifndef CONFIGLOADERERRORHANDLER_H
#define CONFIGLOADERERRORHANDLER_H


#include <xercesc/sax/HandlerBase.hpp>
#include <string>
#include <sstream>

namespace mrifit {
namespace cl {

// \todo Move to own file
/*!
 * \brief An errorhandler for the xerces xml parser.
 * \ingroup group_configloader
 * \todo implement other interface function such as warning...
 */
class ConfigLoaderErrorHandler : public xercesc::HandlerBase
{
public:
    ConfigLoaderErrorHandler() :
        errorMessage_("No error."),
        colnumber_(-1),
        linenumber_(-1)
    {
    }

    virtual ~ConfigLoaderErrorHandler()
    {
    }

    /*!
     * \brief Interface function from xercesc::Handlerbase
     * \param ex
     */
    virtual void error(const xercesc::SAXParseException &ex)
    {
        colnumber_ = ex.getColumnNumber();
        linenumber_ = ex.getLineNumber();
        errorMessage_ = xercesc::XMLString::transcode(ex.getMessage());
    }

    /*!
     * \brief getErrorMessage returns the current error message from the parser.
     * \return
     */
    std::string getErrorMessage()
    {
        std::stringstream stream;
        stream << errorMessage_ << " (Col: " << colnumber_ << ", Line: " << linenumber_ << ")";
        return stream.str();
    }

private:
    std::string errorMessage_;
    int colnumber_;
    int linenumber_;

};

}
}

#endif // CONFIGLOADERERRORHANDLER_H
