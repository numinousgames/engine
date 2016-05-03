// logger.h
#ifndef NGE_UTIL_LOGGER_H
#define NGE_UTIL_LOGGER_H

#include <exception>

#include "engine/strdef.h"
#include "engine/containers/dynamic_array.h"
#include "engine/utility/log.h"

namespace nge
{

namespace util
{

/**
 * Writes messages to a set of logs.
 */
class Logger
{
  private:
    /**
     * The attached logs.
     */
    cntr::DynamicArray<Log*> _logs;

    /**
     * The minimum required level.
     */
    Log::Level _level;

  public:
    // CONSTRUCTION
    /**
     * Constructs a new logger.
     */
    Logger();

    /**
   * Constructs a copy of the logger.
   */
    Logger( const Logger& logger );

    /**
     * Destructs the logger.
     */
    ~Logger();

    // OPERATORS
    /**
     * Assigns as a copy of the logger.
     */
    Logger& operator=( const Logger& logger );

    // MEMBER FUNCTIONS
    /**
     * Sets the minimum log level.
     */
    void setLogLevel( Log::Level level );

    /**
     * Attaches a log to the logger.
     *
     * This will not attach a log that is already attached.
     */
    void attach( Log* log );

    /**
     * Removes the log from the logger.
     */
    void detach( Log* log );

    /**
     * Sends a verbose log message.
     */
    void v( const String& tag, const String& msg );

    /**
     * Sends a verbose log message and log the exception.
     */
    void v( const String& tag, const String& msg, std::exception* exc );

    /**
     * Sends a debug log message.
     */
    void d( const String& tag, const String& msg );

    /**
     * Send a debug log message and log the exception.
     */
    void d( const String& tag, const String& msg, std::exception* exc );

    /**
     * Sends an informational log message.
     */
    void i( const String& tag, const String& msg );

    /**
     * Sends an informational log message and log the exception.
     */
    void i( const String& tag, const String& msg, std::exception* exc );

    /**
     * Sends a warning log message.
     */
    void w( const String& tag, const String& msg );

    /**
     * Send a warning log message and log the exception.
     */
    void w( const String& tag, const String& msg, std::exception* exc );

    /**
     * Sends an error log message.
     */
    void e( const String& tag, const String& msg  );

    /**
     * Send an error log message and log the exception.
     */
    void e( const String& tag, const String& msg, std::exception* exc );

    /**
     * Sends an assertion log message.
     */
    void a( const String& tag, const String& msg );

    /**
     * Send an assertion log message and log the exception.
     */
    void a( const String& tag, const String& msg, std::exception* exc );

    /**
     * Sends a log message.
     */
    void log( Log::Level level, const String& tag, const String& msg );

    /**
     * Send a log message and log the exception.
     */
    void log( Log::Level level, const String& tag, const String& msg,
              std::exception* exc );
};

// MEMBER FUNCTIONS
inline
void Logger::attach( Log* log )
{
    if ( _logs.has( log ) )
    {
        return;
    }

    _logs.push( log );
}

inline
void Logger::detach( Log* log )
{
    _logs.remove( log );
}

inline
void Logger::v( const String& tag, const String& msg )
{
    log( Log::Level::VERBOSE, tag, msg );
}

inline
void Logger::v( const String& tag, const String& msg, std::exception* exc )
{
    log( Log::Level::VERBOSE, tag, msg, exc );
}

inline
void Logger::d( const String& tag, const String& message )
{
    log( Log::Level::DEBUG, tag, message );
}

inline
void Logger::d( const String& tag, const String& msg, std::exception* exc )
{
    log( Log::Level::DEBUG, tag, msg, exc );
}

inline
void Logger::i( const String& tag, const String& msg )
{
    log( Log::Level::INFO, tag, msg );
}

inline
void Logger::i( const String& tag, const String& msg, std::exception* exc )
{
    log( Log::Level::INFO, tag, msg, exc );
}

inline
void Logger::w( const String& tag, const String& msg )
{
    log( Log::Level::WARN, tag, msg );
}

inline
void Logger::w( const String& tag, const String& msg, std::exception* exc )
{
    log( Log::Level::WARN, tag, msg, exc );
}

inline
void Logger::e( const String& tag, const String& msg )
{
    log( Log::Level::ERROR, tag, msg );
}

inline
void Logger::e( const String& tag, const String& msg, std::exception* exc )
{
    log( Log::Level::ERROR, tag, msg, exc );
}

inline
void Logger::a( const String& tag, const String& msg )
{
    log( Log::Level::ASSERT, tag, msg );
}

inline
void Logger::a( const String& tag, const String& msg, std::exception* exc )
{
    log( Log::Level::ASSERT, tag, msg, exc );
}

inline
void Logger::log( Log::Level level, const String& tag, const String& msg )
{
    log( level, tag, msg, nullptr );
}

} // End nspc util

} // End nspc nge

#endif // NGE_UTIL_LOGGER_H
