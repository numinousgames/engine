// vertex_data.h
#ifndef NGE_GRPHX_VERTEX_DATA_H
#define NGE_GRPHX_VERTEX_DATA_H

#include <engine/intdef.h>

namespace nge
{

namespace graphics
{

struct VertexData
{
    uint32 vaoHandle;
    uint32 vboHandle;
};

} // End nspc graphics

} // End nspc nge

#endif // NGE_GRPHX_VERTEX_DATA_H