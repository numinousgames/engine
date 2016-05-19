// window_impl.cpp
#include "engine/rendering/window_impl.h"

namespace nge
{

namespace rndr
{

// HELPER FUNCTIONS
void WindowImpl::setFlag( uint32 mask, bool value )
{
    if ( value )
    {
        _flags |= mask;
    }
    else
    {
        _flags &= ~mask;
    }
}

} // End nspc rndr

} // End nspc nge