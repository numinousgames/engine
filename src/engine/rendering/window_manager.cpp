// window_manager.cpp
#include "engine/rendering/window_manager.h"

namespace nge
{

namespace rndr
{

// GLOBALS
WindowManager WindowManager::g_instance;

// MEMBER FUNCTIONS
void WindowManager::destroyWindow( IWindow* window )
{
    assert( window != nullptr );

    Window* w = dynamic_cast<Window*>( window );

    _windows.remove( w->token() );
    _allocator.release( w, 1 );
}

// HELPER FUNCTIONS
IWindow* WindowManager::createWindow( const String& title, uint32 width,
                                      uint32 height, uint32 x, uint32 y,
                                      bool isFullScreen )
{

    GLFWmonitor* monitor = nullptr;
    int isResizable = GLFW_TRUE;
    if ( isFullScreen )
    {
        monitor = glfwGetPrimaryMonitor();
        isResizable = GLFW_FALSE;
    }

    glfwWindowHint( GLFW_RESIZABLE, isResizable );
    GLFWwindow* w = glfwCreateWindow( width, height, title.c_str(),
                                      monitor, nullptr );
    assert( w != nullptr );

    Window* window = _allocator.get( 1 );
    WindowToken token = getToken( w );
    new ( window ) WindowImpl( w, title, token, width, height, x, y, false );

    glfwSetWindowSizeCallback( w, &WindowManager::onWindowSizeChanged );
    glfwSetWindowPosCallback( w, &WindowManager::onWindowPositionChanged );
    glfwSetWindowFocusCallback( w, &WindowManager::onWindowFocus );

    _windows[getToken( w )] = window;

    glfwSetWindowPos( w, x, y );

    return window;
}

// GLOBAL FUNCTIONS
void WindowManager::onWindowFocus( GLFWwindow* window, int focus )
{
    WindowManager::inst()->_windows[getToken( window )]->
        onFocusChanged( focus == GLFW_TRUE );
}

void WindowManager::onWindowSizeChanged( GLFWwindow* window, int width,
                                         int height )
{
    WindowManager::inst()->_windows[getToken( window )]->
        onSizeChanged( static_cast<uint32>( width ),
                       static_cast<uint32>( height ) );
}

void WindowManager::onWindowPositionChanged( GLFWwindow* window, int x, int y )
{
    WindowManager::inst()->_windows[getToken( window )]->
        onPositionChanged( static_cast<uint32>( x ),
                           static_cast<uint32>( y ) );
}

} // End nspc rndr

} // End nspc nge
