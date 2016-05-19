// window.h
#ifndef NGE_RNDR_IWINDOW_H
#define NGE_RNDR_IWINDOW_H

#include <functional>
#include <engine/strdef.h>

#include "engine/intdef.h"

namespace nge
{

namespace rndr
{

/**
 * Defines a window token.
 */
typedef uintptr WindowToken;

class IWindow
{
  public:
    // CONSTRUCTORS
    /**
     * Destructs the window.
     */
    virtual ~IWindow() = 0;

    // ACCESSOR FUNCTIONS
    /**
     * Gets the window token.
     */
    virtual WindowToken token() const = 0;

    /**
     * Checks if the window is open.
     */
    virtual bool isOpen() const = 0;

    /**
     * Checks if the window should be closed.
     */
    virtual bool shouldClose() const = 0;

    /**
     * CHecks if the window has focus.
     */
    virtual bool hasFocus() const = 0;

    /**
     * Checks if the window size has changed since the last time
     * reset() was called.
     */
    virtual bool wasResized() const = 0;

    /**
     * Checks if the window's screen position has changed since the last time
     * reset() was called.
     */
    virtual bool wasMoved() const = 0;

    /**
     * Checks if the window is being shown.
     */
    virtual bool isVisible() const = 0;

    /**
     * Checks if the window is maximized.
     */
    virtual bool isMaximized() const = 0;

    /**
     * Checks if the window is in full screen mode.
     */
    virtual bool isFullScreen() const = 0;

    /**
     * Checks if this window is the current thread's current context.
     */
    virtual bool isContext() const = 0;

    /**
     * Gets the title.
     */
    virtual const String& title() const = 0;

    /**
     * Gets the x-coordinate of the window's position on the screen.
     */
    virtual uint32 x() const = 0;

    /**
     * Gets the y-coordinate of the window's position on the screen.
     */
    virtual uint32 y() const = 0;

    /**
     * Gets the width in pixels.
     */
    virtual uint32 width() const = 0;

    /**
     * Gets the height in pixels.
     */
    virtual uint32 height() const = 0;

    /**
     * Gets the aspect ratio.
     */
    virtual float aspectRatio() const = 0;

    // MUTATOR METHODS
    /**
     * Sets the window title.
     */
    virtual void setTitle( const String& title ) = 0;

    /**
     * Sets the window icon.
     *
     * This is currently unimplemented.
     */
    virtual void setIcon( uint32 resId ) = 0;

    /**
     * Sets the x coordinate of the window's position on the screen in pixels.
     */
    virtual void setX( uint32 x ) = 0;

    /**
     * Sets the y coordinate of the window's position on the screen in pixels.
     */
    virtual void setY( uint32 y ) = 0;

    /**
     * Moves the window to the specified location on the screen in pixels.
     */
    virtual void moveTo( uint32 x, uint32 y ) = 0;

    /**
     * Sets the width of the window in pixels.
     */
    virtual void setWidth( uint32 width ) = 0;

    /**
     * Sets the height of the window in pixels.
     */
    virtual void setHeight( uint32 height ) = 0;

    /**
     * Resizes the window to the specified width and height in pixels-.
     */
    virtual void resizeTo( uint32 width, uint32 height ) = 0;

    /**
     * Sets the size limits of the window in pixels.
     *
     * Behavior is undefined when:
     * The window is not open.
     */
    virtual void setSizeLimits( uint32 minWidth, uint32 minHeight,
                                uint32 maxWidth, uint32 maxHeight ) = 0;

    // MEMBER FUNCTIONS
    /**
     * Shows the window.
     *
     * This is the same as restoring the window after minimizing it.
     *
     * Behavior is undefined when:
     * The window is not open.
     */
    virtual void show() = 0;

    /**
     * Maximizes the window.
     *
     * Behavior is undefined when:
     * The window is not open.
     */
    virtual void maximize() = 0;

    /**
     * Restores the window to its normal size.
     *
     * Behavior is undefined when:
     * The window is not open.
     */
    virtual void restore() = 0;

    /**
     * Hides the window.
     *
     * This minimizes the window.
     *
     * Behavior is undefined when:
     * THe window is not open.
     */
    virtual void hide() = 0;

    /**
     * Closes the window.
     *
     * Behavior is undefined when:
     * The window is not open.
     */
    virtual void close() = 0;

    /**
     * Polls for new window events.
     *
     * Behavior is undefined when:
     * The window is not open.
     */
    virtual void poll() = 0;

    /**
     * Resets the stateful information like if it was resized or moved.
     */
    virtual void reset() = 0;

    /**
     * Requests that the window gain focus.
     *
     * Behavior is undefined when:
     * The window is not open.
     */
    virtual void requestFocus() = 0;

    /**
     * Makes the window the current context of the current thread.
     *
     * The current context of a thread is the equivalent of the current
     * render target of that thread.
     *
     * Behavior is undefined when:
     * The window is not open.
     */
    virtual void makeContext() = 0;

    /**
     * Swaps the window buffer.
     *
     * Behavior is undefined when:
     * The window is not open.
     */
    virtual void swapBuffer() = 0;
};

// CONSTRUCTORS
inline
IWindow::~IWindow()
{
}

} // End nspc rndr

} // End nspc nge

#endif // NGE_RNDR_IWINDOW_H