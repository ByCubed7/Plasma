// By @ByCubed7 on Twitter

#include "shader.h"

#include <iostream>

Shader::Shader()
{
    program = 0;
}

Shader& Shader::Use()
{
    // Bound the program as we intend on rendering
    glUseProgram(program);
    return *this;
}

void Shader::Compile(const char* vertexSource, const char* fragmentSource, const char* geometrySource)
{
    unsigned int sVertex, sFragment, gShader;
    
    // Vertex Shader
    sVertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(sVertex, 1, &vertexSource, NULL);
    glCompileShader(sVertex);
    checkCompileErrors(sVertex, "VERTEX");
    
    // Fragment Shader
    sFragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(sFragment, 1, &fragmentSource, NULL);
    glCompileShader(sFragment);
    checkCompileErrors(sFragment, "FRAGMENT");
    
    // Geometry shader (if the source code is given)
    if (geometrySource != nullptr)
    {
        gShader = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(gShader, 1, &geometrySource, NULL);
        glCompileShader(gShader);
        checkCompileErrors(gShader, "GEOMETRY");
    }
    
    // Shader program
    program = glCreateProgram();
    glAttachShader(program, sVertex);
    glAttachShader(program, sFragment);
    if (geometrySource != nullptr)
        glAttachShader(program, gShader);
    glLinkProgram(program);
    checkCompileErrors(program, "PROGRAM");
    
    // Delete the shaders
    glDeleteShader(sVertex);
    glDeleteShader(sFragment);
    if (geometrySource != nullptr)
        glDeleteShader(gShader);
}

void Shader::SetFloat(const char* name, float value, bool useShader)
{
    if (useShader) Use();
    glUniform1f(glGetUniformLocation(program, name), value);
}
void Shader::SetInteger(const char* name, int value, bool useShader)
{
    if (useShader) Use();
    glUniform1i(glGetUniformLocation(program, name), value);
}
void Shader::SetVector2(const char* name, int x, int y, bool useShader)
{
    if (useShader) Use();
    glUniform2i(glGetUniformLocation(program, name), x, y);
}
void Shader::SetVector2f(const char* name, float x, float y, bool useShader)
{
    if (useShader) Use();
    glUniform2f(glGetUniformLocation(program, name), x, y);
}
void Shader::SetVector2f(const char* name, const glm::vec2& value, bool useShader)
{
    if (useShader) Use();
    glUniform2f(glGetUniformLocation(program, name), value.x, value.y);
}
void Shader::SetVector3f(const char* name, float x, float y, float z, bool useShader)
{
    if (useShader) Use();
    glUniform3f(glGetUniformLocation(program, name), x, y, z);
}
void Shader::SetVector3f(const char* name, const glm::vec3& value, bool useShader)
{
    if (useShader) Use();
    glUniform3f(glGetUniformLocation(program, name), value.x, value.y, value.z);
}
void Shader::SetVector4f(const char* name, float x, float y, float z, float w, bool useShader)
{
    if (useShader) Use();
    glUniform4f(glGetUniformLocation(program, name), x, y, z, w);
}
void Shader::SetVector4f(const char* name, const glm::vec4& value, bool useShader)
{
    if (useShader) Use();
    glUniform4f(glGetUniformLocation(program, name), value.x, value.y, value.z, value.w);
}
void Shader::SetMatrix4(const char* name, const glm::mat4& matrix, bool useShader)
{
    if (useShader) Use();
    glUniformMatrix4fv(glGetUniformLocation(program, name), 1, false, glm::value_ptr(matrix));
}


void Shader::checkCompileErrors(unsigned int object, std::string type)
{
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(object, 1024, NULL, infoLog);
            std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
                << infoLog << "\n -- --------------------------------------------------- -- "
                << std::endl;
        }
    }
    else
    {
        glGetProgramiv(object, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(object, 1024, NULL, infoLog);
            std::cout << "| ERROR::Shader: Link-time error: Type: " << type << "\n"
                << infoLog << "\n -- --------------------------------------------------- -- "
                << std::endl;
        }
    }
}