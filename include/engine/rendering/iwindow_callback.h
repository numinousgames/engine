// iwindow_callback.h
#ifndef NGE_RNDR_IWINDOW_CALLBACK
#define NGE_RNDR_IWINDOW_CALLBACK

#include "engine/intdef.h"

namespace nge
{

namespace rndr
{

class IWindowCallback
{
  public:
    // CONSTRUCTORS
    virtual ~IWindowCallback() = 0;

    // MEMBER FUNCTIONS
    /**
     * Called by the window manager when this changes focus.
     */
    virtual void onFocusChanged( bool focused ) = 0;

    /**
     * Called by the window manager when this changes position.
     */
    virtual void onPositionChanged( uint32 x, uint32 y ) = 0;

    /**
     * Called by the window manager when this changes size.
     */
    virtual void onSizeChanged( uint32 width, uint32 height ) = 0;
};

// CONSTRUCTORS
inline
IWindowCallback::~IWindowCallback()
{
}

} // End nspc rndr

} // End nspc nge

#endif // NGE_RNDR_IWINDOW_CALLBACK
