// By @ByCubed7 on Twitter


//#define VERBOSE

#include "shader.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include <glad.h>
#include <glm/gtc/type_ptr.hpp>


inline bool ends_with(std::string const& value, std::string const& ending)
{
    if (ending.size() > value.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}


Shader::Shader()
{
    program = 0;
}

Shader::~Shader()
{
    //std::cout << "[Shader::Use] Dtor: " << program << std::endl;
    //glDeleteProgram(program);
    //program = 0;
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
    
    // Set up Program
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

Shader& Shader::SetFloat(const char* name, float value, bool useShader)
{
    if (useShader) Use();
    glUniform1f(glGetUniformLocation(program, name), value);
    return *this;
}
Shader& Shader::SetInteger(const char* name, int value, bool useShader)
{
    if (useShader) Use();
    glUniform1i(glGetUniformLocation(program, name), value);
    return *this;
}
Shader& Shader::SetVector2(const char* name, int x, int y, bool useShader)
{
    if (useShader) Use();
    glUniform2i(glGetUniformLocation(program, name), x, y);
    return *this;
}
Shader& Shader::SetVector2f(const char* name, float x, float y, bool useShader)
{
    if (useShader) Use();
    glUniform2f(glGetUniformLocation(program, name), x, y);
    return *this;
}
Shader& Shader::SetVector2f(const char* name, const glm::vec2& value, bool useShader)
{
    if (useShader) Use();
    glUniform2f(glGetUniformLocation(program, name), value.x, value.y);
    return *this;
}
Shader& Shader::SetVector3f(const char* name, float x, float y, float z, bool useShader)
{
    if (useShader) Use();
    glUniform3f(glGetUniformLocation(program, name), x, y, z);
    return *this;
}
Shader& Shader::SetVector3f(const char* name, const glm::vec3& value, bool useShader)
{
    if (useShader) Use();
    glUniform3f(glGetUniformLocation(program, name), value.x, value.y, value.z);
    return *this;
}
Shader& Shader::SetVector4f(const char* name, float x, float y, float z, float w, bool useShader)
{
    if (useShader) Use();
    glUniform4f(glGetUniformLocation(program, name), x, y, z, w);
    return *this;
}
Shader& Shader::SetVector4f(const char* name, const glm::vec4& value, bool useShader)
{
    if (useShader) Use();
    glUniform4f(glGetUniformLocation(program, name), value.x, value.y, value.z, value.w);
    return *this;
}
Shader& Shader::SetMatrix4(const char* name, const glm::mat4& matrix, bool useShader)
{
    if (useShader) Use();
    glUniformMatrix4fv(glGetUniformLocation(program, name), 1, false, glm::value_ptr(matrix));
    return *this;
}

Shader Shader::FromFile(const std::string filename)
{
    std::string filetype = ".shader";
    // Filename is EXPECTED to end with filetype
    if (!ends_with(filename, filetype)) std::cout << "Shader::FromFile::Error: Filename does not end with `" << filetype << "`" << std::endl;

    // Get the shader filepath
    std::string filepath = filename.substr(0, filename.size() - filetype.size());
    std::string vShaderFile = filepath + ".vs";
    std::string fShaderFile = filepath + ".frag";
    std::string gShaderFile = filepath + ".geog";

    // Retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;

    // Whether the code has loaded correctly
    bool vertexLoaded = false;
    bool fragmentLoaded = false;
    bool geometryLoaded = false;

    // Open files
    std::ifstream vertexShaderFile(vShaderFile);
    std::ifstream fragmentShaderFile(fShaderFile);
    std::ifstream geometryShaderFile(gShaderFile);

    if (vertexShaderFile.good())
    {
        std::stringstream vShaderStream;
        vShaderStream << vertexShaderFile.rdbuf(); // Read file buffer contents into stream
        vertexCode = vShaderStream.str(); // Convert stream into string
        vertexLoaded = true;
    }

    if (fragmentShaderFile.good())
    {
        std::stringstream fShaderStream;
        fShaderStream << fragmentShaderFile.rdbuf(); // Read file buffer contents into stream
        fragmentCode = fShaderStream.str(); // Convert stream into string
        fragmentLoaded = true;
    }

    if (geometryShaderFile.good())
    {
        std::stringstream gShaderStream;
        gShaderStream << geometryShaderFile.rdbuf(); // Read file buffer contents into stream
        geometryCode = gShaderStream.str(); // Convert stream into string
        geometryLoaded = true;
    }

    // Close file handlers
    vertexShaderFile.close();
    fragmentShaderFile.close();
    geometryShaderFile.close();

    // -

    //if (!vertexLoaded) std::cout << "Vertex shader NOT loaded." << std::endl;
    //if (!fragmentLoaded) std::cout << "Fragment shader NOT loaded." << std::endl;
    //if (!geometryLoaded) std::cout << "Geometry shader NOT loaded." << std::endl;
    
    // -

    // Create shader object from source code
    Shader shader = Shader();
    shader.Compile(
        vertexCode.c_str(),
        fragmentCode.c_str(),
        geometryLoaded ? geometryCode.c_str() : nullptr
    );

    return shader;
}

void Shader::Clear()
{
    glDeleteProgram(program);
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