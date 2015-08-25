#ifndef _ZIA_API_ILOG_H_
#define _ZIA_API_ILOG_H_

#include <sstream>
#include <iostream>

#include "defines.hpp"

_BOF_ZIA_API_

/*!
 * \brief Log class
 *
 * <h2> Zia core implementations: </h2>
 * \code

//
// Minimal ILog inherits implementation:
//
namespace zia {

class X : public api::ILog
{
public:
    X();
    virtual ~X();

    virtual void        print(Level level, const std::string& format, ...) = 0;
    virtual ILog&       operator << (Level level) = 0;

    // tell to the compiler that this exists in ILog
    using api::ILog::operator <<;

};

}

 * \endcode
 *
 */
class ILog
{
public:

    /*!
     * \brief Log levels
     */
    enum Level
    {
        ERROR = 1,
        WARNING,
        INFO,
        DEBUG,
        DEBUG2
    };

    /*!
     * \brief Constructor.
     */
    ILog() { }

    /*!
     * \brief Destructor.
     */
    virtual ~ILog() { }

    /*!
     * \brief Printf like.
     *
     * \param level The ILog::Level.
     * \param format The format string for printf.
     * \param ... Values corresponding to the format.
     */
    virtual void        print(Level level, const std::string& format, ...) = 0;

    /*!
     * \brief Set the current log level.
     *
     * eg:
     * \code

ILog     log;

log << ILog::DEBUG << "coucou " << 42;
log << ILog::ERROR << "poney " << 273;

     * \endcode
     */
    virtual ILog&       operator << (Level level) = 0;

    /*!
     * \brief C++ output stream like.
     *
     * This is a template because it permits to work
     * automativaly with every type:
     *
     * eg:
     * \code

ILog     log;

log << "toto";  // automaticaly: operator << ( const char[4] & input )
log << 42;      // automaticaly: operator << ( const int & input )
log << 18.5;    // automaticaly: operator << ( const double & input )

     * \endcode
     */
    template <typename T>
    ILog&               operator << (const T& input)
    {
        mStream << input;
        return (*this);
    }

protected:
    /*!
     * \brief Log buffer.
     */
    std::stringstream   mStream;

};

_EOF_ZIA_API_

#endif /* _ZIA_API_ILOG_H_ */
