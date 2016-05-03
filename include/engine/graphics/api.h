// api.h
//
// Handles importing and initializing the appropriate grphx api as well
// as defining the core types. In addition this defines C++ wrappers for
// the various grphx api's. It is important to note that for different
// underlying API's the defined will differ drastically.
//
// TODO: generate system.g.h file which describes the target system.
//
#ifndef NGE_GRPHX_API_H
#define NGE_GRPHX_API_H

#include <engine/intdef.h>

namespace nge
{

namespace grphx
{

///**
// * Defines a grphx handle.
//// */
////typedef uint32 GlHandle;

//struct Grapi
//{
//    /**
//     * Creates the specified number of handles.
//     *
//     * Behavior is undefined when:
//     * handles is null or not at an array of size count.
//     */
//    static void createBuffers( GlHandle* handle);
//
//    /**
//     * Destroys and releases the given handles.
//     */
//    static void destroyBuffers( GlHandle* handles );
//};

} // End nspc grphx

} // End nspc nge

#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>

#endif // NGE_GRPHX_API_H
