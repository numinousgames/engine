// program.cpp
#include "engine/graphics/program.h"

#include "engine/graphics/api.h"

namespace nge
{

namespace grphx
{

bool Program::load()
{
    return load( nullptr );
}

bool Program::load( const Shader::LogCallback& callback )
{
    return load( &callback );
}

void Program::bind()
{
    if ( isBound() || !isLoaded() )
    {
        return;
    }

    glUseProgram( _binding );
    _isBound = true;
}

void Program::unbind()
{
    if ( !isBound() || !isLoaded() )
    {
        return;
    }

    glUseProgram( 0 );
    _isBound = false;
}

void Program::unload()
{
    if ( !isLoaded() )
    {
        return;
    }

    glDeleteProgram( _binding );
    _binding = 0;


}

// HELPER FUNCTIONS
bool Program::load( const Shader::LogCallback* callback )
{
    if ( isLoaded() )
    {
        return false;
    }

    if ( !loadShaders( callback ) )
    {
        return false;
    }

    _binding = glCreateProgram();

    for ( auto iter = _shaders.cbegin();
          iter != _shaders.cend();
          ++iter )
    {
        glAttachShader( _binding, iter->value.binding() );
    }
}

bool Program::loadShaders( const Shader::LogCallback* callback )
{
    bool wasSuccessful = true;
    for ( auto iter = _shaders.cbegin();
          iter != _shaders.cend();
          ++iter )
    {
        if ( callback != nullptr )
        {
            wasSuccessful &= _shaders[iter->key].load( *callback );
        }
        else
        {
            wasSuccessful &= _shaders[iter->key].load();
        }
    }

    // unload on failure
    if ( !wasSuccessful )
    {
        for ( auto iter = _shaders.cbegin();
              iter != _shaders.cend();
              ++iter )
        {
            if ( _shaders[iter->key].isLoaded() )
            {
                _shaders[iter->key].unload();
            }
        }
    }

    return wasSuccessful;
}

} // End nspc grphx

} // End nspc nge