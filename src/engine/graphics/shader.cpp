// shader.cpp
#include "engine/graphics/shader.h"

#include <fstream>
#include "engine/containers/fixed_array.h"
#include "engine/graphics/api.h"

namespace nge
{

namespace grphx
{

// MEMBER FUNCTIONS
bool Shader::load( const LogCallback& callback )
{
    if ( isLoaded() )
    {
        callback( "Shader Load Error: Shader is already loaded." );
        return false;
    }

    callback( "Loading Shader" );
    callback( "Path: " + _path );
    callback( "Type: " + std::to_string( _stage ) );

    uint32 status = loadShader();
    if ( status == STATUS_FILE_NOT_FOUND )
    {
        callback( "Shader Load Error: File not found." );
        return false;
    }

    // check for compilation log
    int32 logLength;
    glGetShaderiv( _binding, GL_INFO_LOG_LENGTH, &logLength );

    if ( logLength <= 0 )
    {
        return status == STATUS_SUCCESS;
    }

    // read compilation log
    cntr::FixedArray<char> msg( static_cast<uint32>( logLength ) );
    glGetShaderInfoLog( _binding, logLength, nullptr, msg.data() );

    callback( "Shader Compilation Log" );
    callback( msg.data() );

    return status == STATUS_SUCCESS;
}

void Shader::unload()
{
    if ( !isLoaded() )
    {
        return;
    }

    glDeleteShader( _binding );
    _binding = 0;
    _isLoaded = false;
}

// HELPER FUNCTIONS
uint32 Shader::loadShader()
{
    // reads the file
    String content;
    std::ifstream file( _path, std::ios::in );
    if ( !file.is_open() )
    {
        return STATUS_FILE_NOT_FOUND;
    }

    String line = "";
    while ( !file.eof() )
    {
        std::getline( file, line );
        content.append( line + "\n" );
    }

    file.close();

    // compiles the shader
    _binding = glCreateShader( getShaderType() );

    const char* src = content.c_str();
    glShaderSource( _binding, 1, &src, nullptr );

    glCompileShader( _binding );

    // check for success
    int32 status;
    glGetShaderiv( _binding, GL_COMPILE_STATUS, &status );

    if ( status == GL_TRUE )
    {
        _isLoaded = true;
        return STATUS_SUCCESS;
    }
    else
    {
        return STATUS_COMPILATION_FAILURE;
    }
}

uint32 Shader::getShaderType() const
{
    uint32 type;
    switch ( _stage )
    {
        case VERTEX:
            type = GL_VERTEX_SHADER;
            break;

        case TESSELLATION_CONTROL:
            type = GL_TESS_CONTROL_SHADER;
            break;

        case TESSELLATION_EVALUATION:
            type = GL_TESS_EVALUATION_SHADER;
            break;

        case GEOMETRY:
            type = GL_GEOMETRY_SHADER;
            break;

        case FRAGMENT:
            type = GL_FRAGMENT_SHADER;
            break;

#ifdef GL_COMPUTE_SHADER
        case COMPUTE:
            type = GL_COMPUTE_SHADER;
            break;
#endif

        default:
            type = 0;
            break;
    }

    return type;
}

} // End nspc grphx

} // End nspc nge