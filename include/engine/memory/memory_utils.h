// memory_utils.h
#ifndef NGE_MEM_MEMORY_UTILS_H
#define NGE_MEM_MEMORY_UTILS_H

#include <utility>

#include "engine/intdef.h"

namespace nge
{

namespace mem
{

struct MemoryUtils
{
  public:
    /**
     * Copies items from the source to the destination.
     */
    template <typename T>
    static void copy( T* dst, T* src, uint32 count );

    /**
     * Moves items from the source to the destination.
     */
    template <typename T>
    static void move( T* dst, T* src, uint32 count );

    /**
     * Sets the all of the values in the array to the given value.
     */
    template <typename T>
    static void set( T* ptr, const T& value, uint32 count );
};

template <typename T>
void MemoryUtils::copy( T* dst, T* src, uint32 count )
{
    uint32 i;
    for ( i = 0; i < count; ++i )
    {
        dst[i] = src[i];
    }
}

template <typename T>
void MemoryUtils::move( T* dst, T* src, uint32 count )
{
    uint32 i;
    for ( i = 0; i < count; ++i )
    {
        dst[i] = std::move( src[i] );
    }
}

template <typename T>
void MemoryUtils::set( T* ptr, const T& value, uint32 count )
{
    uint32 i;
    for ( i = 0; i < count; ++i )
    {
        ptr[i] = value;
    }
}

} // End nspc mem

} // End nspc nge

#endif // NGE_MEM_MEMORY_UTILS_H