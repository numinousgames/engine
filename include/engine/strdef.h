// strdef.h
#ifndef NGE_STRDEF_H
#define NGE_STRDEF_H

#include <string>

namespace nge
{

// STRINGS
/**
 * Defines a string.
 *
 * This exists so that transitioning to a custom string implementation will
 * be easier.
 */
typedef std::string String;

} // End nspc nge

#endif // NGE_STRDEF_H
