// program.h
//
// Defines a shading program.
//
// A program is a set of shaders that can be bound.
//
#ifndef NGE_GRPHX_PROGRAM_H
#define NGE_GRPHX_PROGRAM_H

#include "engine/strdef.h"
#include "engine/containers/map.h"
#include "engine/graphics/shader.h"

namespace nge
{

namespace grphx
{

class Program
{
  private:
    // MEMBERS
    /**
     * The registered shaders.
     */
    cntr::Map<Shader::Stage, Shader> _shaders;

//    /**
//     * The attributes.
//     * GL - Attributes
//     * DX - Data Buffer
//     */
//    cntr::Map<String, uint32> _attributes;

//    /**
//     * The constants..
//     * GL - Uniforms
//     * DX - Constant Buffer
//     */
//    cntr::Map<String, uint32> _constants;

    /**
     * The program name.
     */
    String _name;

    /**
     * The program language.
     */
    String _language;

    /**
     * The program binding.
     */
    uint32 _binding;

    /**
     * If the program is bound.
     */
    bool _isBound;

    /**
     * If the program is loaded.
     */
    bool _isLoaded;

    // HELPER FUNCTIONS
    /**
     * Loads the program.
     *
     * This allows a callback to optionally be provided.
     */
    bool load( const Shader::LogCallback* callback );

    /**
     * Loads the shaders.
     */
    bool loadShaders( const Shader::LogCallback* callback );

  public:
    // CONSTRUCTORS
    /**
     * Constructs a new unnamed shading program.
     */
    Program();

    /**
     * Constructs a new shading program with the given name.
     */
    Program( const String& name );

    /**
     * Constructs a copy of a given program.
     *
     * This will not copy the bindings.
     */
    Program( const Program& program );

    /**
     * Constructs a program by moving the resources to this instance.
     *
     * This will move the shaders instances causing this program to
     * have none.
     *
     * This will move bindings causing the source program to no longer
     * have valid.
     */
    Program( Program&& program );

    /**
     * Destructs the shading program.
     *
     * The program must be unloaded or else a mem leak will occur
     * on the GPU.
     */
    ~Program();

    // OPERATORS
    /**
     * Assigns this as a copy of the given program.
     *
     * This will not copy bindings and must be reloaded.
     *
     * Behavior is undefined when:
     * The program being reassigned is already loaded.
     * The program being reassigned is already bound.
     */
    Program& operator=( const Program& program );

    /**
     * Assigns this as the given program.
     *
     * This will move the shaders instances causing this program to
     * have none.
     *
     * This will move bindings causing the source program to no longer
     * have valid.
     */
    Program& operator=( Program&& program );

    // ACCESSOR FUNCTIONS
    /**
     * Gets the program name.
     */
    const String& name() const;

    /**
     * Gets the required shader language for the set.
     *
     * This is set once the first shader is added thus requiring subsequent
     * shaders to be in the same language.
     *
     * This returns an emtpy string if no shaders have been added yet.
     */
    const String& language() const;

    /**
     * Gets if the shader set is bound to the GPU.
     */
    bool isBound() const;

    /**
     * Gets if the program is loaded.
     */
    bool isLoaded() const;

    // MUTATOR FUNCTIONS
    /**
     * Sets the program's name.
     */
    void setName( const String& name );

    // MEMBER FUNCTIONS
    /**
     * Adds the given shader.
     *
     * This will overwrite any shader that is already registered for the
     * specified stage.
     *
     * Throws runtime_error when:
     * The shader's language is inconsistent with the others.
     * The program is loaded.
     */
    void addShader( const Shader& shader );
;;
    /**
     * Removes the shader that is registered for the specified stage.
     *
     * Throws runtime_error when:
     * The program is loaded.
     *
     * Behavior is undefined when:
     * There is not a shader registered for the specified stage.
     */
    void removeShader( Shader::Stage stage );

    /**
     * Gets the shader registered for the specified shading stage.
     *
     * Behavior is undefined when:
     * The specified stage does not have a registered shader.
     */
    const Shader& getShader( Shader::Stage stage ) const;

    /**
     * Checks if a shader is registered for the specified stage.
     */
    bool hasShader( Shader::Stage stage ) const;

    /**
     * Loads the assigned shaders.
     *
     * Returns if it was successful.
     *
     * Throws runtime_error when:
     * There are not shaders for all of the required stages.
     */
    bool load();

    /**
     * Loads the assigned shaders.
     *
     * Status messages will be sent to the provided callback.
     * Returns if it was successful.
     *
     * Throws runtime_error when:
     * There are not shaders for all of the required stages.
     */
    bool load( const Shader::LogCallback& callback );

    /**
     * Binds the set of shaders on the GPU.
     */
    void bind();

    /**
     * Unbinds the set of shaders on the GPU.
     */
    void unbind();

    /**
     * Unloads the program.
     */
    void unload();
};

// CONSTRUCTORS
inline
Program::Program() : _shaders(), _name(), _language(), _binding( 0 ),
                     _isBound( false ), _isLoaded( false )
{
}

inline
Program::Program( const String& name )
    : _shaders(), _name( name ), _language(), _binding( 0 ), _isBound( false ),
      _isLoaded( false )
{
}

inline
Program::Program( const Program& program )
    : _shaders( program._shaders ), _name( program._name ),
      _language( program._language ), _binding( 0 ), _isBound( false ),
      _isLoaded( false )
{
}

inline
Program::Program( Program&& program )
    : _shaders( std::move( program._shaders ) ), _name( program._name ),
      _language( program._language ), _binding( program._binding ),
      _isBound( program._isBound ), _isLoaded( program._isLoaded )
{
    program._binding = 0;
    program._isBound = false;
    program._isLoaded = false;
}

inline
Program::~Program()
{
    assert( !isBound() );
    assert( !isLoaded() );
}

// OPERATORS
inline
Program& Program::operator=( const Program& program )
{
    assert( !isBound() );
    assert( !isLoaded() );

    _shaders = program._shaders;
    _name = program._name;
    _language = program._language;
    _binding = 0;
    _isBound = false;
    _isLoaded = false;

    return *this;
}

inline
Program& Program::operator=( Program&& program )
{
    assert( !isBound() );
    assert( !isLoaded() );

    _shaders = std::move( program._shaders );
    _name = program._name;
    _language = program._language;
    _binding = program._binding;
    _isBound = program._isBound;
    _isLoaded = program._isLoaded;

    program._language = "";
    program._binding = 0;
    program._isBound = false;
    program._isLoaded = false;

    return *this;
}

// ACCESSOR FUNCTIONS
inline
const String& Program::name() const
{
    return _name;
}

inline
const String& Program::language() const
{
    return _language;
}

inline
bool Program::isBound() const
{
    return _isBound;
}

inline
bool Program::isLoaded() const
{
    return _isLoaded;
}

// MUTATOR FUNCTIONS
inline
void Program::setName( const String& name )
{
    _name = name;
}

// MEMBER FUNCTIONS
inline
void Program::addShader( const Shader& shader )
{
    if ( isLoaded() )
    {
        throw std::runtime_error( "Program cannot be modified while loaded!" );
    }

    if ( _language.length() > 0 && _language != shader.language() )
    {
        throw std::runtime_error( "The shader's language is inconsistent "
                                      "with the existing shaders!" );
    }

    _shaders.put( shader.stage(), shader );
}

inline
void Program::removeShader( Shader::Stage stage )
{
    if ( isLoaded() )
    {
        throw std::runtime_error( "Program cannot be modified while loaded!" );
    }

    _shaders.remove( stage );
}

inline
const Shader& Program::getShader( Shader::Stage stage ) const
{
    assert( _shaders.has( stage ) );
    return _shaders[stage];
}

inline
bool Program::hasShader( Shader::Stage stage ) const
{
    return _shaders.has( stage );
}

} // End npsc grphx

} // End nspc nge

#endif // NGE_GRPHX_PROGRAM_H