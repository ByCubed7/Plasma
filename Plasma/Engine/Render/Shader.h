// By @ByCubed7 on Twitter

#pragma once

#include "../Resource.h"

#include <glm/glm.hpp>
#include <string>

// General purpose shader class.
class Shader : public Resource<Shader>
{
public:
    // State
    unsigned int program;

    // Default Constructor
    Shader();

    // Default Deconstructor - frees the associated memory for this shader
    // Genenerally, this deconstructor shouldn't be called.
    ~Shader();

    /// <summary>
    /// Tell OpenGL to use this Shader.
    /// </summary>
    /// <returns>Self for method chaining</returns>
    Shader& Use();

    /// <summary>
    /// Compiles the shader from some given source code
    /// </summary>
    /// <param name="vertexSource">- the pointer to the vertex source code.</param>
    /// <param name="fragmentSource">- the pointer to the fragment source code.</param>
    /// <param name="geometrySource">- the pointer to the vertex source code. (optional)</param>
    void Compile(const char* vertexSource, const char* fragmentSource, const char* geometrySource = nullptr); 


    // - Utility functions
    
    /// <summary> Sets a float uniform in the shader.</summary>
    /// <param name="name">- the name of the Uniform.</param> <param name="value">- the value to set it to.</param> 
    /// <param name="useShader">- whether to tell OpenGL to use the shader.</param>
    Shader& SetFloat(const char* name, float value, bool useShader = false);

    /// <summary> Sets an int uniform in the shader.</summary>
    /// <param name="name">- the name of the Uniform.</param> <param name="value">- the value to set it to.</param> 
    /// <param name="useShader">- whether to tell OpenGL to use the shader.</param>
    Shader& SetInteger(const char* name, int value, bool useShader = false);

    /// <summary> Sets an ivec2 uniform in the shader.</summary>
    /// <param name="name">- the name of the Uniform.</param> <param name="value">- the value to set it to.</param> 
    /// <param name="useShader">- whether to tell OpenGL to use the shader.</param>
    Shader& SetVector2(const char* name, int x, int y, bool useShader = false);

    /// <summary> Sets an vec2 uniform in the shader.</summary>
    /// <param name="name">- the name of the Uniform.</param> <param name="value">- the value to set it to.</param> 
    /// <param name="useShader">- whether to tell OpenGL to use the shader.</param>
    Shader& SetVector2f(const char* name, float x, float y, bool useShader = false);

    /// <summary> Sets an vec3 uniform in the shader.</summary>
    /// <param name="name">- the name of the Uniform.</param> <param name="value">- the value to set it to.</param> 
    /// <param name="useShader">- whether to tell OpenGL to use the shader.</param>
    Shader& SetVector2f(const char* name, const glm::vec2& value, bool useShader = false);

    /// <summary> Sets an vec3 uniform in the shader.</summary>
    /// <param name="name">- the name of the Uniform.</param> <param name="value">- the value to set it to.</param> 
    /// <param name="useShader">- whether to tell OpenGL to use the shader.</param>
    Shader& SetVector3f(const char* name, float x, float y, float z, bool useShader = false);

    /// <summary> Sets an vec3 uniform in the shader.</summary>
    /// <param name="name">- the name of the Uniform.</param> <param name="value">- the value to set it to.</param> 
    /// <param name="useShader">- whether to tell OpenGL to use the shader.</param>
    Shader& SetVector3f(const char* name, const glm::vec3& value, bool useShader = false);

    /// <summary> Sets an vec4 uniform in the shader.</summary>
    /// <param name="name">- the name of the Uniform.</param> <param name="value">- the value to set it to.</param> 
    /// <param name="useShader">- whether to tell OpenGL to use the shader.</param>
    Shader& SetVector4f(const char* name, float x, float y, float z, float w, bool useShader = false);

    /// <summary> Sets an vec4 uniform in the shader.</summary>
    /// <param name="name">- the name of the Uniform.</param> <param name="value">- the value to set it to.</param> 
    /// <param name="useShader">- whether to tell OpenGL to use the shader.</param>
    Shader& SetVector4f(const char* name, const glm::vec4& value, bool useShader = false);

    /// <summary> Sets an mat4 uniform in the shader.</summary>
    /// <param name="name">- the name of the Uniform.</param> <param name="value">- the value to set it to.</param> 
    /// <param name="useShader">- whether to tell OpenGL to use the shader.</param>
    Shader& SetMatrix4(const char* name, const glm::mat4& matrix, bool useShader = false);


protected:
    Shader FromFile(const std::string filename) override;
    void Clear() override;

private:
    /// <summary>
    /// Checks if compilation or linking failed and if so, print the error logs.
    /// </summary>
    /// <param name="object">The object pointer</param>
    /// <param name="type">The shader or program type.</param>
    void checkCompileErrors(unsigned int object, std::string type);
};
