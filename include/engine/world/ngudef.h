// ngudef.h
#ifndef NGE_WORLD_NGUDEF_H
#define NGE_WORLD_NGUDEF_H

namespace nge
{

namespace world
{

/**
 * Defines numinous game units.
 */
typedef float ngu;

typedef float MM;

typedef float CM;

typedef float M;

typedef float KM;

constexpr KM operator "" _km( long double value )
{
    return KM( value );
}

} // End nspc world

} // End nspc nge

#endif // NGE_WORLD_NGUDEF_H