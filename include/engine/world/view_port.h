// view_port.h
#ifndef NGE_WORLD_VIEW_PORT_H
#define NGE_WORLD_VIEW_PORT_H

#include "engine/rendering/window.h"
#include "engine/world/ngudef.h"

namespace nge
{

namespace world
{

class ViewPort
{
  private:
    // MEMBERS
    /**
     * The window that the view port is being displayed in.
     */
    rndr::Window* _window;

    /**
     * The height of the view port in numinous game units.
     */
    ngu _height;

    /**
     * The x coordinate of the view port.
     */
    ngu _x;

    /**
     * The y coordinate of the view port.
     */
    ngu _y;

    /**
     * Counter-clockwise rotation.
     *
     * This is measured from the positive x-axis and is performed along the
     * z-axis that is perpendicular to the window located at the center of
     * the viewport..
     */
    // TODO: use rotation
    ngu _rotation;

    /**
     * The world to window scale factor.
     */
    float _scaleFactor;

    /**
     * Recalculates the scale factor.
     */
    void updateScaleFactor();

  public:
    // CONSTRUCTORS
    /**
     * Constructs a new view port.
     */
    ViewPort();

    /**
     * Constructs a new view port with the given window.
     */
    ViewPort( rndr::Window* window, ngu height );

    /**
     * Constructs a copy of the view port.
     */
    ViewPort( const ViewPort& viewPort );

    /**
     * Destructs the view port.
     */
    ~ViewPort();

    // OPERATORS
    /**
     * Assigns this as a copy of the view port.
     */
    ViewPort& operator=( const ViewPort& viewPort );

    // ACCESSOR FUNCTIONS
    /**
     * Gets the x-coordinate in numinous game units.
     */
    ngu x() const;

    /**
     * Gets the y-coordinate in numinous game units.
     */
    ngu y() const;

    /**
     * Gets the width in numinous game units.
     */
    ngu width() const;

    /**
     * Gets the height in numinous game units.
     */
    ngu height() const;

    /**
     * Gets the world to window scale factor.
     */
    ngu scaleFactor() const;

    // MUTATOR FUNCTIONS
    /**
     * Sets the x-coordinate.
     */
    void setX( ngu x );

    /**
     * Sets the y-coordinate.
     */
    void setY( ngu y );

    /**
     * Sets the viewport height in numinous game units.
     *
     * This will auto scale the width to maintain the aspect ratio.
     */
    void setHeight( ngu height );

    /**
     * Sets the viewport width in numinous game units.
     *
     * This will auto scale the height to maintain the aspect ratio.
     */
    void setWidth( ngu width );

    // MEMBER FUNCTIONS
    /**
     * Offsets the view port position by the given ammounts.
     */
    void offsetBy( ngu dx, ngu dy );

    /**
     * Sets the current coordinates.
     */
    void moveTo( ngu x, ngu y );
};

// CONSTRUCTORS
inline
ViewPort::ViewPort() : _window( nullptr ), _height( 0.0f ), _x( 0.0f ),
                       _y( 0.0f ), _rotation( 0.0f )
{
}

inline
ViewPort::ViewPort( rndr::Window* window, ngu height )
    : _window( window ), _height( height ), _x( 0.0f ), _y( 0.0f ),
      _rotation( 0.0f )
{
}

inline
ViewPort::ViewPort( const ViewPort& viewPort )
    : _window( viewPort._window ), _height( viewPort._height ),
      _x( viewPort._x ), _y( viewPort._y ), _rotation( viewPort._rotation )
{
}

inline
ViewPort::~ViewPort()
{
    _window = nullptr;
    _height = 0.0f;
    _x = 0.0f;
    _y = 0.0f;
    _rotation = 0.0f;
}

// OPERATORS
inline
ViewPort& ViewPort::operator=( const ViewPort& viewPort )
{
    _window = viewPort._window;
    _height = viewPort._height;
    _x = viewPort._x;
    _y = viewPort._y;
    _rotation = viewPort._rotation;

    return *this;
}

// ACCESSOR FUNCTIONS
inline
ngu ViewPort::x() const
{
    return _x;
}

inline
ngu ViewPort::y() const
{
    return _y;
}

inline
ngu ViewPort::width() const
{
    assert( _window != nullptr );
    return _height * _window->aspectRatio();
}

inline
ngu ViewPort::height() const
{
    return _height;
}

inline
float ViewPort::scaleFactor() const
{
    return _scaleFactor;
}

// MUTATOR FUNCTIONS
inline
void ViewPort::setX( ngu x )
{
    _x = x;
}

inline
void ViewPort::setY( ngu y )
{
    _y = y;
}

inline
void ViewPort::setHeight( ngu height )
{
    _height = height;
    updateScaleFactor();
}

inline
void ViewPort::setWidth( ngu width )
{
    assert( _window != nullptr );
    _height = width / ( _window->aspectRatio() );
    updateScaleFactor();
}

// MEMBER FUNCTIONS
inline
void ViewPort::offsetBy( ngu dx, ngu dy )
{
    _x += dx;
    _y += dy;
}

inline
void ViewPort::moveTo( ngu x, ngu y )
{
    _x = x;
    _y = y;
}

// HELPER FUNCTIONS
inline
void ViewPort::updateScaleFactor()
{
    _scaleFactor = static_cast<float>( _window->height() ) /
        static_cast<float>( height() );
}

} // End nspc world

} // End nspc nge

#endif // NGE_WORLD_VIEW_PORT_H
