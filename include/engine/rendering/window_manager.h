// window_manager.h
#ifndef NGE_RNDR_WINDOW_MANAGER
#define NGE_RNDR_WINDOW_MANAGER

#include "engine/containers/list.h"
#include "engine/containers/map.h"
#include "engine/rendering/iwindow.h"
#include "engine/rendering/window_impl.h"

namespace nge
{

namespace rndr
{

class WindowManager
{
  private:
    // TYPES
    /**
     * Defines a window implementation.
     */
    typedef WindowImpl Window;

    // GLOBALS
    /**
     * The singleton window manager.
     */
    static WindowManager g_instance;

    // MEMBERS
    /**
     * The window allocator.
     */
    mem::AllocatorGuard<Window> _allocator;

    /**
     * The handle to window map.
     */
    cntr::Map<WindowToken, IWindowCallback*> _windows;

    // CONSTRUCTORS
    /**
     * Constructs the window manager.
     */
    WindowManager();

    /**
     * Deleted constructor.
     */
    WindowManager( const WindowManager& manager ) = delete;

    // OPERATORS
    /**
     * Deleted operator.
     */
    WindowManager& operator=( const WindowManager& manager ) = delete;

    // HELPER FUNCTIONS
    /**
     * Creates a new window.
     */
    IWindow* createWindow( const String& title, uint32 width,
                           uint32 height, uint32 x, uint32 y,
                           bool isFullScreen );

    // GLOBAL FUNCTIONS
    /**
     * Called when a window gains focus.
     */
    static void onWindowFocus( GLFWwindow* window, int focus );

    /**
     * Called when a window is resized.
     */
    static void onWindowSizeChanged( GLFWwindow* window, int width,
                                     int height );

    /**
     * Called when a window is moved.
     */
    static void onWindowPositionChanged( GLFWwindow* window, int x, int y );

    /**
     * Gets a token for the specified window.
     */
    static WindowToken getToken( GLFWwindow* window );

  public:
    // CONSTRUCTORS
    /**
     * Destructs the window manager.
     */
    ~WindowManager();

    // MEMBER FUNCTIONS
    /**
     * Creates a new window.
     */
    IWindow* createWindow( const String& title, uint32 width, uint32 height );

    /**
     * Creates a new window.
     */
    IWindow* createWindow( const String& title, uint32 width, uint32 height,
                           uint32 x, uint32 y );

    /**
     * Creates a new full screen window.
     */
    IWindow* createFullScreenWindow( const String& title, uint32 width,
                                     uint32 height );

    /**
     * Destroys the specified window.
     *
     * Behavior is undefined when:
     * The window is invalid.
     */
    void destroyWindow( IWindow* window );

    // GLOBAL FUNCTIONS
    /**
     * Gets the singleton instance of the window manager.
     */
    static WindowManager* inst();
};

// CONSTRUCTORS
inline
WindowManager::WindowManager() : _windows()
{
    glfwInit();
}

inline
WindowManager::~WindowManager()
{
    for ( auto iter = _windows.cbegin(); iter != _windows.cend(); ++iter )
    {
        _allocator.release( dynamic_cast<Window*>( iter->value ), 1 );
    }
}

// MEMBER FUNCTIONS
inline
IWindow* WindowManager::createWindow( const String& title, uint32 width,
                                      uint32 height )
{
    return createWindow( title, width, height, 0, 0, false );
}

inline
IWindow* WindowManager::createWindow( const String& title, uint32 width,
                                      uint32 height, uint32 x, uint32 y )
{
    return createWindow( title, width, height, x, y, false );
}

inline
IWindow* WindowManager::createFullScreenWindow( const String& title,
                                                uint32 width, uint32 height )
{
    return createWindow( title, width, height, 0, 0, true );
}

// GLOBAL FUNCTIONS
inline
WindowManager* WindowManager::inst()
{
    return &g_instance;
}

inline
WindowToken WindowManager::getToken( GLFWwindow* window )
{
    return reinterpret_cast<WindowToken>( window );
}

} // End nspc rndr

} // End nspc nge

#endif // NGE_RNDR_WINDOW_MANAGER
