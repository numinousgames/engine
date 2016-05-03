// convex_shape.h
//
// A 2D simple convex shape with a given number of points.
//
// Internally the center point is always the first point and is always
// assumed to be the 2D zero vector and it is incorrect to position the
// outer points in a fashion in which the center point is not zero.
// As such all transforms must be performed using a transformation matrix.
//
// This class is not meant to be used directly and should instead be
// inherited with a more specific context such as a rectangle.
//
#ifndef NGE_GRPHX_CONVEX_SHAPE_H
#define NGE_GRPHX_CONVEX_SHAPE_H

#include <engine/containers/fixed_array.h>
#include <engine/rendering/irenderable.h>
#include <engine/math/vec.h>

namespace nge
{

namespace grphx
{

class ConvexShape : public rndr::IRenderable
{
  private:
    // CONSTANTS
    /**
     * Flag: The verts need to be resent to the GPU.
     */
    static constexpr uint32 FLAG_VERTS_DIRTY = 0x20000000;

    /**
     * Flag: The shape has data on the gpu.
     *
     * This does not mean that the data is up to date.
     */
    static constexpr uint32 FLAG_GPU = 0x40000000;

    /**
     * Flag: The shape is visible.
     */
    static constexpr uint32 FLAG_VISIBLE = 0x80000000;

    // MEMBERS
    /**
     * The vertices.
     */
    cntr::FixedArray<math::Vec2> _verts;

    /**
     * The state flags.
     */
    uint32 _flags;

    /**
     * The vertex array object.
     */
    uint32 _vao;

    /**
     * The vertex buffer object.
     */
    uint32 _vbo;

    // HELPER FUNCTIONS
    /**
     * Pushes the data to the gpu.
     */
    void push();

    /**
     * Releases the data from the cpu.
     */
    void release();

    /**
     * Fills the remaining spaces with zero vectors.
     */
    void fillVerts( cntr::FixedArray<math::Vec2>* verts );

    /**
     * Sets a flag value.
     */
    void setFlag( uint32 mask, bool value );

    /**
     * Checks if the flag is set.
     */
    bool checkFlag( uint32 mask );

  public:
    // CONSTRUCTORS
    /**
     * Constructs a new convex shape with zero outer vertices.
     */
    ConvexShape();

    /**
     * Constructs a new convex shape with the given number of outer vertices.
     *
     * Behavior is undefined when:
     * vertexCount is less than 2
     */
    ConvexShape( uint32 vertexCount );

    /**
     * Constructs a copy of the given convex shape.
     */
    ConvexShape( const ConvexShape& shape );

    /**
     * Destructs the convex shape.
     */
    virtual ~ConvexShape();

    // MEMBER FUNCTIONS
    /**
     * Gets the number of vertices in the shape.
     */
    uint32 vertexCount() const;

    /**
     * Sets the vertex count for the shape.
     *
     * This will maintain as many vertices as possible.
     *
     * Behavior is undefined when:
     * count is less than 2
     */
    void setVertexCount( uint32 count );

    /**
     * Gets the vertex at the given index.
     *
     * Behavior is undefined when:
     * index is out of bounds.
     */
    math::Vec2 getVertex( uint32 index );

    /**
     * Sets the value of one of the shape's vertices.
     *
     * Behavior is undefined when:
     * The index is out of bounds.
     */
    void setVertex( uint32 index, math::Vec2 vert );

    /**
     * Draws the shape.
     */
    virtual void draw();
};

// CONSTANTS
constexpr uint32 ConvexShape::FLAG_GPU;

constexpr uint32 ConvexShape::FLAG_VERTS_DIRTY;

constexpr uint32 ConvexShape::FLAG_VISIBLE;

// CONSTRUCTORS
inline
ConvexShape::ConvexShape() : ConvexShape( 2 )
{
}

inline
ConvexShape::ConvexShape( uint32 vertexCount )
    : _verts( vertexCount + 1 ), _flags( 0 )
{
    assert( vertexCount >= 2 );
    setFlag( FLAG_VISIBLE, true );
    setFlag( FLAG_VERTS_DIRTY, true );
    fillVerts( &_verts );
}

inline
ConvexShape::ConvexShape( const ConvexShape& shape )
    : _verts( shape._verts ), _flags( shape._flags )
{
    setFlag( FLAG_GPU, false );
    setFlag( FLAG_VERTS_DIRTY, true );
}

inline
ConvexShape::~ConvexShape()
{
    if ( checkFlag( FLAG_GPU ) )
    {
        release();
    }
}

// MEMBER FUNCTIONS
inline
uint32 ConvexShape::vertexCount() const
{
    return _verts.size() - 1;
}

inline
math::Vec2 ConvexShape::getVertex( uint32 index )
{
    assert( index + 1 < _verts.size() );
    return _verts[index + 1];
}

inline
void ConvexShape::setVertex( uint32 index, math::Vec2 vert )
{
    assert( index + 1 < _verts.size() );

    if ( _verts[++index] == vert )
    {
        return;
    }

    _verts[index] = vert;
    setFlag( FLAG_VERTS_DIRTY, true );
}

// HELPER FUNCTIONS
inline
void ConvexShape::setFlag( uint32 mask, bool value )
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

inline
bool ConvexShape::checkFlag( uint32 mask )
{
    return ( _flags & mask ) != 0;
}

} // End nspc grphx

} // End nspc nge

#endif // NGE_GRPHX_CONVEX_SHAPE_H
