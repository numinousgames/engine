// shader.h
#ifndef NGE_GRPHX_SHADER_H
#define NGE_GRPHX_SHADER_H

#include <assert.h>
#include <functional>
#include "engine/intdef.h"
#include "engine/strdef.h"

namespace nge
{

namespace grphx
{

class Shader
{
  public:
    // TYPES
    /**
     * A shader gpu binding.
     */
    typedef uint32 Binding;

    // ENUMERATIONS
    /**
     * The rndr stages.
     */
    enum Stage : uint32;

  private:
    // CONSTANTS
    /**
     * Load Status: Success.
     */
    static constexpr uint32 STATUS_SUCCESS = 0;

    /**
     * Load Status: File could not be found.
     */
    static constexpr uint32 STATUS_FILE_NOT_FOUND = 1;

    /**
     * Load Status: Failed to compile.
     */
    static constexpr uint32 STATUS_COMPILATION_FAILURE = 2;

    // MEMBERS
    /**
     * The file path to the shader.
     */
    String _path;

    /**
     * The shader language.
     */
    String _language;

    /**
     * The associated shader stage.
     */
    Stage _stage;

    /**
     * The shader binding.
     */
    Binding _binding;

    /**
     * If the shader is loaded.
     */
    bool _isLoaded;

    // HELPER FUNCTIONS
    /**
     * Loads the shader and compiles it on the GPU.
     *
     * Returns the status code.
     */
    uint32 loadShader();

    /**
     * Gets the api specific shader type.
     */
    uint32 getShaderType() const;

  public:
    // TYPES
    /**
     * Defines a callback that is used for logging messages.
     *
     * Each message should be considered a different line.
     */
    // todo: replace with logger
    typedef std::function<void( const String& msg )> LogCallback;

    // ENUMERATIONS
    /**
     * The rndr stages.
     */
    enum Stage : uint32
    {
        VERTEX = 0,
        TESSELLATION_CONTROL,
        TESSELLATION_EVALUATION,
        GEOMETRY,
        FRAGMENT,
        COMPUTE
    };

    // CONSTRUCTORS
    /**
     * Constructs an uninitialized shader.
     */
    Shader();

    /**
     * Constructs a new shader.
     */
    Shader( Stage stage, const String& path, const String& language );

    /**
     * Constructs a copy of the given shader.
     *
     * This will not copy bindings and must be reloaded.
     */
    Shader( const Shader& shader );

    /**
     * Constructs a shader by moving the resources to this instance.
     *
     * This will move bindings causing the source shader to no longer
     * have valid references.
     */
    Shader( Shader&& shader );

    /**
     * Destructs the shader.
     *
     * The shader must not be loaded when this is called.
     */
    ~Shader();

    // OPERATORS
    /**
     * Assigns this as a copy of the given shader.
     *
     * This will not use the same bindings as the source and will
     * not be loaded.
     */
    Shader& operator=( const Shader& shader );

    /**
     * Assigns this as the given program.
     *
     * This will move bindings causing the source shader to no longer
     * have valid references.
     */
    Shader& operator=( Shader&& shader );

    // ACCESSOR FUNCTIONS
    /**
     * Gets the file path.
     */
    const String& path() const;

    /**
     * Gets the shader language.
     */
    const String& language() const;

    /**
     * Gets the associated rndr stage.
     */
    Stage stage() const;

    /**
     * Gets the GPU binding.
     *
     * This value is only meaningful while the shader is loaded.
     */
    Binding binding() const;

    /**
     * Checks if the shader is loaded on the GPU.
     */
    bool isLoaded() const;

    // MEMBER FUNCTIONS
    /**
     * Loads the shader onto the GPU.
     *
     * Returns if it was successful.
     */
    bool load();

    /**
     * Loads the shader onto the GPU.
     *
     * Status messages will be sent to the provided callback.
     * Returns if it was successful.
     */
    bool load( const LogCallback& callback );

    /**
     * Unloads the shader from GPU.
     *
     * This must be explicitly called after calling load. Failure to do so
     * will cause a mem leak on the GPU.
     */
    void unload();
};

// CONSTRUCTORS
inline
Shader::Shader() : _path(), _language(), _stage(), _binding( 0 ),
                   _isLoaded( false )
{
}

inline
Shader::Shader( Stage stage, const String& path, const String& language )
    : _path( path ), _language( language ), _stage( stage ), _binding( 0 ),
      _isLoaded( false )
{
}

inline
Shader::Shader( const Shader& shader )
    : _path( shader._path ), _language( shader._language ),
      _stage( shader._stage ), _binding( 0 ), _isLoaded( false )
{
}

inline
Shader::Shader( Shader&& shader )
    : _path( shader._path ), _language( shader._language ),
      _stage( shader._stage ), _binding( shader._binding ),
      _isLoaded( shader._isLoaded )
{
    shader._binding = 0;
    shader._isLoaded = false;
}

inline
Shader::~Shader()
{
    assert( !isLoaded() );
}

// OPERATORS
inline
Shader& Shader::operator=( const Shader& shader )
{
    assert( !isLoaded() );

    _path = shader._path;
    _language = shader._language;
    _stage = shader._stage;
    _binding = 0;
    _isLoaded = false;

    return *this;
}

inline
Shader& Shader::operator=( Shader&& shader )
{
    assert( !isLoaded() );

    _path = shader._path;
    _language = shader._language;
    _stage = shader._stage;
    _binding = shader._binding;
    _isLoaded = shader._isLoaded;

    shader._binding = 0;
    shader._isLoaded = false;

    return *this;
}

// ACCESSOR FUNCTIONS
inline
const String& Shader::path() const
{
    return _path;
}

inline
const String& Shader::language() const
{
    return _language;
}

inline
Shader::Stage Shader::stage() const
{
    return _stage;
}

inline
Shader::Binding Shader::binding() const
{
    return _binding;
}

inline
bool Shader::isLoaded() const
{
    return _isLoaded;
}

// MEMBER FUNCTIONS
inline
bool Shader::load()
{
    if ( isLoaded() )
    {
        return false;
    }

    return STATUS_SUCCESS == loadShader();
}

} // End nspc grphx

} // End nspc nge

#endif // NGE_GRPHX_SHADER_H