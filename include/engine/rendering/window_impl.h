// window_impl.h
//
// The concrete implementation of the window.
//
// This should only be constructed by the WindowManager.
//
#ifndef NGE_RNDR_WINDOW_IMPL
#define NGE_RNDR_WINDOW_IMPL

#include <GLFW/glfw3.h>
#include <iostream>

#include "engine/containers/dynamic_array.h"
#include "engine/rendering/iwindow.h"
#include "engine/rendering/iwindow_callback.h"

namespace nge
{

namespace rndr
{

class WindowImpl : public IWindow, public IWindowCallback
{
  private:
    /**
     * Flag: Has focus?
     */
    static constexpr uint32 FLAG_HAS_FOCUS = 0x2;

    /**
     * Flag: Was resized since last poll?
     */
    static constexpr uint32 FLAG_WAS_RESIZED = 0x4;

    /**
     * Flag: Was moved?
     */
    static constexpr uint32 FLAG_WAS_MOVED = 0x8;

    /**
     * Flag: Is visible?
     */
    static constexpr uint32 FLAG_VISIBLE= 0x10;

    /**
     * Flag: is maximized?
     */
    static constexpr uint32 FLAG_MAXIMIZED = 0x20;

    /**
     * Flag: Is in full screen mode?
     */
    static constexpr uint32 FLAG_FULL_SCREEN = 0x40;

    /**
     * The underlying window.
     */
    GLFWwindow* _window;

    /**
     * The window token.
     */
    WindowToken _token;

    /**
     * The window title.
     */
    String _title;

    /**
     * The window icon.
     */
    uint32 _icon;

    /**
     * The window width.
     */
    uint32 _width;

    /**
     * The window height.
     */
    uint32 _height;

    /**
     * The x coordinate of the position.
     */
    uint32 _x;

    /**
     * The y coordinate of the position.
     */
    uint32 _y;

    /**
     * The window flags.
     */
    uint32 _flags;

    // CONSTRUCTORS
    /**
     * Disabled: windows cannot be copied.
     */
    WindowImpl( const WindowImpl& window ) = delete;

    // OPERATORS
    /**
     * Disabled: windows cannot be copied.
     */
    WindowImpl& operator=( const WindowImpl& window ) = delete;

    // HELPER METHODS
    /**
     * Sets a flag value.
     */
    void setFlag( uint32 mask, bool value );

    /**
     * Checks a flag value.
     */
    bool checkFlag( uint32 mask ) const;

  public:
    // CONSTRUCTORS
    /**
     * Constructs a new, invalid, window.
     */
    WindowImpl();

    /**
     * Constructs a new window.
     */
    WindowImpl( GLFWwindow* window, const String& title, WindowToken token,
                uint32 width, uint32 height, uint32 x, uint32 y,
                bool isFullScreen );

    /**
     * Destructs the window.
     */
    virtual ~WindowImpl();

    // ACCESSOR FUNCTIONS
    /**
     * Gets the window token.
     */
    virtual WindowToken token() const;

    /**
     * Checks if the window is open.
     */
    virtual bool isOpen() const;

    /**
     * Checks if the window should be closed.
     *
     * Behavior is undefined when:
     * The window is not open.
     */
    virtual bool shouldClose() const;

    /**
     * CHecks if the window has focus.
     */
    virtual bool hasFocus() const;

    /**
     * Checks if the window size has changed since the last time
     * reset() was called.
     */
    virtual bool wasResized() const;

    /**
     * Checks if the window's screen position has changed since the last time
     * reset() was called.
     */
    virtual bool wasMoved() const;

    /**
     * Checks if the window is being shown.
     */
    virtual bool isVisible() const;

    /**
     * Checks if the window is maximized.
     */
    virtual bool isMaximized() const;

    /**
     * Checks if the window is in full screen mode.
     */
    virtual bool isFullScreen() const;

    /**
     * Checks if this window is the current thread's current context.
     */
    virtual bool isContext() const;

    /**
     * Gets the title.
     */
    virtual const String& title() const;

    /**
     * Gets the x-coordinate of the window's position on the screen.
     */
    virtual uint32 x() const;

    /**
     * Gets the y-coordinate of the window's position on the screen.
     */
    virtual uint32 y() const;

    /**
     * Gets the width in pixels.
     */
    virtual uint32 width() const;

    /**
     * Gets the height in pixels.
     */
    virtual uint32 height() const;

    /**
     * Gets the aspect ratio.
     */
    virtual float aspectRatio() const;

    // MUTATOR METHODS
    /**
     * Sets the window title.
     */
    virtual void setTitle( const String& title );

    /**
     * Sets the window icon.
     *
     * This is currently unimplemented.
     */
    virtual void setIcon( uint32 resId );

    /**
     * Sets the x coordinate of the window's position on the screen in pixels.
     */
    virtual void setX( uint32 x );

    /**
     * Sets the y coordinate of the window's position on the screen in pixels.
     */
    virtual void setY( uint32 y );

    /**
     * Moves the window to the specified location on the screen in pixels.
     */
    virtual void moveTo( uint32 x, uint32 y );

    /**
     * Sets the width of the window in pixels.
     */
    virtual void setWidth( uint32 width );

    /**
     * Sets the height of the window in pixels.
     */
    virtual void setHeight( uint32 height );

    /**
     * Resizes the window to the specified width and height in pixels-.
     */
    virtual void resizeTo( uint32 width, uint32 height );

    /**
     * Sets the size limits of the window in pixels.
     *
     * Behavior is undefined when:
     * The window is not open.
     */
    virtual void setSizeLimits( uint32 minWidth, uint32 minHeight,
                                uint32 maxWidth, uint32 maxHeight );

    // MEMBER FUNCTIONS
    /**
     * Shows the window.
     *
     * This is the same as restoring the window after minimizing it.
     *
     * Behavior is undefined when:
     * The window is not open.
     */
    virtual void show();

    /**
     * Maximizes the window.
     *
     * Behavior is undefined when:
     * The window is not open.
     */
    virtual void maximize();

    /**
     * Restores the window to its normal size.
     *
     * Behavior is undefined when:
     * The window is not open.
     */
    virtual void restore();

    /**
     * Hides the window.
     *
     * This minimizes the window.
     *
     * Behavior is undefined when:
     * THe window is not open.
     */
    virtual void hide();

    /**
     * Closes the window.
     *
     * Behavior is undefined when:
     * The window is not open.
     */
    virtual void close();

    /**
     * Polls for new window events.
     *
     * Behavior is undefined when:
     * The window is not open.
     */
    virtual void poll();

    /**
     * Resets the stateful information like if it was resized or moved.
     */
    virtual void reset();

    /**
     * Requests that the window gain focus.
     *
     * Behavior is undefined when:
     * The window is not open.
     */
    virtual void requestFocus();

    /**
     * Makes the window the current context of the current thread.
     *
     * The current context of a thread is the equivalent of the current
     * render target of that thread.
     *
     * Behavior is undefined when:
     * The window is not open.
     */
    virtual void makeContext();

    /**
     * Swaps the window buffer.
     *
     * Behavior is undefined when:
     * The window is not open.
     */
    virtual void swapBuffer();

    // CALLBACK FUNCTIONS
    /**
     * Called by the window manager when this changes focus.
     */
    virtual void onFocusChanged( bool focused );

    /**
     * Called by the window manager when this changes position.
     */
    virtual void onPositionChanged( uint32 x, uint32 y );

    /**
     * Called by the window manager when this changes size.
     */
    virtual void onSizeChanged( uint32 width, uint32 height );
};

// CONSTRUCTORS
inline
WindowImpl::WindowImpl()
    : _window( nullptr ), _token( 0 ), _title(), _width( 0 ), _height( 0 ),
      _x( 0 ), _y( 0 ), _flags( 0 )
{
}

inline
WindowImpl::WindowImpl( GLFWwindow* window, const String& title,
                        WindowToken token, uint32 width, uint32 height,
                        uint32 x, uint32 y, bool isFullScreen )
    : _window( window ), _title( title ), _token( token ),
      _width( width ), _height( height ), _x( x ), _y( y )
{
    setFlag( FLAG_FULL_SCREEN, isFullScreen );
}

inline
WindowImpl::~WindowImpl()
{
    if ( isOpen() )
    {
        close();
    }
}

// ACCESSOR FUNCTIONS
inline
WindowToken WindowImpl::token() const
{
    return _token;
}

inline
bool WindowImpl::isOpen() const
{
    return _window != nullptr;
}

inline
bool WindowImpl::shouldClose() const
{
    assert( _window != nullptr );
    return glfwWindowShouldClose( _window ) == GLFW_TRUE;
}

inline
bool WindowImpl::hasFocus() const
{
    return checkFlag( FLAG_HAS_FOCUS );
}

inline
bool WindowImpl::wasResized() const
{
    return checkFlag( FLAG_WAS_RESIZED );
}

inline
bool WindowImpl::wasMoved() const
{
    return checkFlag( FLAG_WAS_MOVED );
}

inline
bool WindowImpl::isVisible() const
{
    return checkFlag( FLAG_VISIBLE );
}

inline
bool WindowImpl::isMaximized() const
{
    return checkFlag( FLAG_MAXIMIZED );
}

inline
bool WindowImpl::isFullScreen() const
{
    return checkFlag( FLAG_FULL_SCREEN );
}

inline
bool WindowImpl::isContext() const
{
    return glfwGetCurrentContext() == _window;
}

inline
const String& WindowImpl::title() const
{
    return _title;
}

inline
uint32 WindowImpl::x() const
{
    return _x;
}

inline
uint32 WindowImpl::y() const
{
    return _y;
}

inline
uint32 WindowImpl::width() const
{
    return _width;
}

inline
uint32 WindowImpl::height() const
{
    return _height;
}

inline
float WindowImpl::aspectRatio() const
{
    return static_cast<float>( _width ) / static_cast<float>( _height );
}

// MUTATOR FUNCTIONS
inline
void WindowImpl::setTitle( const String& title )
{
    _title = title;
    if ( isOpen() )
    {
        glfwSetWindowTitle( _window, title.c_str() );
    }
}

inline
void WindowImpl::setIcon( uint32 resId )
{
    _icon = resId;
    // todo: update icon
}

inline
void WindowImpl::setX( uint32 x )
{
    _x = x;
    if ( isOpen() )
    {
        glfwSetWindowPos( _window, x, y() );
    }
}

inline
void WindowImpl::setY( uint32 y )
{
    _y = y;
    if ( isOpen() )
    {
        glfwSetWindowPos( _window, x(), y );
    }
}

inline
void WindowImpl::moveTo( uint32 x, uint32 y )
{
    _x = x;
    _y = y;
    if ( isOpen() )
    {
        glfwSetWindowPos( _window, x, y );
    }
}

inline
void WindowImpl::setWidth( uint32 width )
{
    _width = width;
    if ( isOpen() )
    {
        glfwSetWindowSize( _window, width, height() );
    }
}

inline
void WindowImpl::setHeight( uint32 height )
{
    _height = height;
    if ( isOpen() )
    {
        glfwSetWindowSize( _window, width(), height );
    }
}

inline
void WindowImpl::resizeTo( uint32 width, uint32 height )
{
    _width = width;
    _height = height;
    if ( isOpen() )
    {
        glfwSetWindowSize( _window, width, height );
    }
}

inline
void WindowImpl::setSizeLimits( uint32 minWidth, uint32 minHeight,
                                uint32 maxWidth, uint32 maxHeight )
{
    assert( isOpen() );
    glfwSetWindowSizeLimits( _window, minWidth, minHeight,
                             maxWidth, maxHeight );
}

// MEMBER FUNCTIONS
inline
void WindowImpl::show()
{
    assert( isOpen() );

    glfwShowWindow( _window );
    setFlag( FLAG_VISIBLE, true );
}

inline
void WindowImpl::maximize()
{
    assert( isOpen() );

    glfwMaximizeWindow( _window );
    setFlag( FLAG_MAXIMIZED, true );
}

inline
void WindowImpl::restore()
{
    assert( isOpen() );

    glfwRestoreWindow( _window );
    setFlag( FLAG_MAXIMIZED, false );
}

inline
void WindowImpl::hide()
{
    assert( isOpen() );

    glfwHideWindow( _window );
    setFlag( FLAG_VISIBLE, false );
}

inline
void WindowImpl::close()
{
    assert( isOpen() );

    glfwDestroyWindow( _window );
    _window = nullptr;
}

inline
void WindowImpl::poll()
{
    assert( isOpen() );
    glfwPollEvents();
}

inline
void WindowImpl::reset()
{
    setFlag( FLAG_WAS_RESIZED, false );
    setFlag( FLAG_WAS_MOVED, false );
}

inline
void WindowImpl::requestFocus()
{
    assert( isOpen() );

    glfwFocusWindow( _window );
    setFlag( FLAG_HAS_FOCUS, true );
}

inline
void WindowImpl::makeContext()
{
    assert( _window != nullptr );
    glfwMakeContextCurrent( _window );
}

inline
void WindowImpl::swapBuffer()
{
    assert( isOpen() );
    glfwSwapBuffers( _window );
}

inline
void WindowImpl::onFocusChanged( bool focused )
{
    setFlag( FLAG_HAS_FOCUS, focused );
}

inline
void WindowImpl::onPositionChanged( uint32 x, uint32 y )
{
    _x = x;
    _y = y;
    setFlag( FLAG_WAS_MOVED, true );
}

inline
void WindowImpl::onSizeChanged( uint32 width, uint32 height )
{
    _width = width;
    _height = height;
    setFlag( FLAG_WAS_RESIZED, true );
}

// HELPER FUNCTIONS
inline
bool WindowImpl::checkFlag( uint32 mask ) const
{
    return ( _flags & mask ) != 0;
}

} // End nspc rndr

} // End nspc nge

#endif
