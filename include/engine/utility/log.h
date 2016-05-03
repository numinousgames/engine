// log.h
//
// Interface definition of a log.
//
// Logs can be used to track runtime information.
//
#ifndef NGE_UTIL_LOG_H
#define NGE_UTIL_LOG_H

#include <exception>

#include "engine/strdef.h"

namespace nge
{

namespace util
{

class Log
{
  public:
    // ENUMERATIONS
    enum Level
    {
        VERBOSE = 0,
        DEBUG,
        INFO,
        WARN,
        ERROR,
        ASSERT
    };

    // CONSTRUCTORS
    /**
     * Destructs the log.
     */
    virtual ~Log() = 0;

    // MEMBER FUNCTIONS
    /**
     * Sets the log level.
     */
    virtual void setLevel( Level level ) = 0;

    /**
     * Logs the given message.
     */
    virtual void write( Level level, const String& tag, const String& msg,
                        std::exception exc ) = 0;
};

// CONSTRUCTORS
inline
Log::~Log()
{
}

} // End nspc util

} // End nspc nge

#endif // NGE_UTIL_LOG_H
