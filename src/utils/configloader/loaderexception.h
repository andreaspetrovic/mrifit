#ifndef LOADEREXCEPTION_H
#define LOADEREXCEPTION_H


namespace mrifit {
namespace cl {



/*!
 * \brief The LoaderException class
 * \ingroup group_configloader
 */
class LoaderException : public std::exception
{
public:
    LoaderException() : std::exception(), message_("Loader Excpetion occured!")
    {
    }
    LoaderException(std::string message) : std::exception(), message_(message)
    {
    }
    virtual ~LoaderException() throw()
    {
    }
    virtual const char* what() const throw()
    {
        std::string dummyMessage("LoaderException: " + message_);
        return dummyMessage.c_str();
    }

private:
    std::string message_;
};

}
}

#endif // LOADEREXCEPTION_H
