// gr_api.h
//
// Defines a simple OpenGL C++ wrapper.
//
#ifndef NGE_GRPHX_GL_API_H
#define NGE_GRPHX_GL_API_H

#include <engine/intdef.h>
#include <GL/gl.h>

namespace nge
{

namespace graphics
{

typedef GLuint Program;
typedef GLuint Shader;
typedef GLuint ArrayBuffer;
typedef GLuint VertexBuffer;

struct ModelData
{
    ArrayBuffer vao;
    VertexBuffer vbo;
};

} // End nspc graphics

} // End nspc nge

#endif // NGE_GRPHX_GL_API_H
