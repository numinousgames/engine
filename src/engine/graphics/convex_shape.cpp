// convex_shape.cpp
#include "engine/graphics/convex_shape.h"
#include "engine/graphics/api.h"

namespace nge
{

namespace grphx
{

// MEMBER FUNCTIONS
void ConvexShape::setVertexCount( uint32 count )
{
    assert( count >= 2 );

    cntr::FixedArray<math::Vec2> arr( ++count );
    int i;

    for ( i = 0; i < count && i < _verts.size(); ++i )
    {
        arr.push( _verts[i] );
    }

    fillVerts( &arr );

    _verts = std::move( arr );

    setFlag( FLAG_VERTS_DIRTY, true );
}

void ConvexShape::draw()
{
    if ( !checkFlag( FLAG_VISIBLE ) )
    {
        return;
    }

    if ( checkFlag( FLAG_VERTS_DIRTY ) )
    {
        push();
    }

    glBindVertexArray( _vao );

    // todo: pass paint
    // todo: apply transformation uniform

    // points
    glDrawArrays( GL_POINTS, 1, _verts.size() - 1 );

    // outline
    glDrawArrays( GL_LINE_LOOP, 1, _verts.size() - 1 );

    // fill
    glDrawArrays( GL_TRIANGLE_FAN, 0, _verts.size() );

    glBindVertexArray( 0 );
}

// HELPER FUNCTIONS
void ConvexShape::fillVerts( cntr::FixedArray<math::Vec2>* verts )
{
    while ( verts->size() < verts->capacity() )
    {
        verts->push( math::Vec2( 0, 0 ) );
    }
}

void ConvexShape::push()
{
    if ( checkFlag( FLAG_GPU ) )
    {
        glBindBuffer( GL_ARRAY_BUFFER, _vbo );
        glBufferData( GL_ARRAY_BUFFER, _verts.size() * 2 * sizeof( GLfloat ),
                      _verts.data(), GL_STATIC_DRAW );
        glBindBuffer( GL_ARRAY_BUFFER, 0 );
        return;
    }

    glGenVertexArrays( 1, &_vao );
    glBindVertexArray( _vao );

    glGenBuffers( 1, &_vbo );
    glBindBuffer( GL_ARRAY_BUFFER, _vbo );
    glBufferData( GL_ARRAY_BUFFER, _verts.size() * 2 * sizeof( GLfloat ),
                  _verts.data(), GL_STATIC_DRAW );

    glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 0, 0 );
    glEnableVertexAttribArray( 0 );

    glBindBuffer( GL_ARRAY_BUFFER, 0 );
    glBindVertexArray( 0 );

    setFlag( FLAG_GPU, true );
}

void ConvexShape::release()
{
    if ( checkFlag( FLAG_GPU ) )
    {
        glDeleteBuffers( 1, &_vbo );
        glDeleteVertexArrays( 1, &_vao );
    }
}

} // End nspc grphx

} // End nspc nge