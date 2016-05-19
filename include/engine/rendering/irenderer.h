// irenderer.h
//
// Tracks all of the renderable entities and handles drawing them.
//
// The renderable type is left ambiguous so that any rndr technique
// or organization can be utilized such as CPU rndr or letting
// renderables draw themselves as compared to the renderer containing
// the draw code.
//
// Renderer implementations must disable their copy constructor and assignment
// operator.
//
#ifndef NGE_RNDR_IRENDERER_H
#define NGE_RNDR_IRENDERER_H

#include "engine/intdef.h"
#include "engine/rendering/irenderable.h"
#include "engine/rendering/iwindow.h"

namespace nge
{

namespace rndr
{

template <typename R>
class IRenderer
{
  public:
    // CONSTRUCTORS
    /**
     * Destructs the renderer.
     */
    virtual ~IRenderer() = 0;

    // MEMBER FUNCTIONS
    /**
     * Adds a renderable to the scene.
     */
    virtual void addRenderable( R* renderable ) = 0;

    /**
     * Removes the renderable from the scene.
     */
    virtual void removeRenderable( R* renderable ) = 0;

    /**
     * Removes all renderables from the scene.
     */
    virtual void removeAllRenderables() = 0;

    /**
     * Attaches to the specified window.
     */
    virtual void attach( IWindow* window ) = 0;

    /**
     * Draws the scene.
     */
    virtual void draw() = 0;

    /**
     * Detaches from the current window.
     */
    virtual void detach() = 0;

    /**
     * Checks if the renderer is attached to a window.
     */
    virtual bool isAttached() const = 0;

    /**
     * Checks if the renderer is currently rndr.
     */
    virtual bool isActive() const = 0;
};

// CONSTRUCTORS
template <typename R>
inline
IRenderer<R>::~IRenderer()
{
}

} // End nspc rndr

} // End nspc nge

#endif // NGE_RNDR_IRENDERER_H
