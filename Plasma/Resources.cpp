#include <iostream>
#include <sstream>
#include <fstream>

#include "Resources.h"

#include "Library/stb_image.h"

// Cache any resources we load
std::map<std::string, Texture2D> Resources::Textures;
std::map<std::string, Shader> Resources::Shaders;


Shader Resources::LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name)
{
    Shaders[name] = LoadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
    return Shaders[name];
}

Shader& Resources::GetShader(std::string name)
{
    return Shaders[name];
}

Texture2D Resources::LoadTexture(const char* file, bool alpha, std::string name)
{
    Textures[name] = LoadTextureFromFile(file, alpha);
    return Textures[name];
}

Texture2D& Resources::GetTexture(std::string name)
{
    return Textures[name];
}



//

void Resources::Clear()
{
    // Delete all the shaders and textures
    for (auto iter : Shaders) glDeleteProgram(iter.second.Program);
    for (auto iter : Textures) glDeleteTextures(1, &iter.second.ID);
}

Shader Resources::LoadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile)
{
    // Retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;

    try
    {
        // Open files
        std::ifstream vertexShaderFile(vShaderFile);
        std::ifstream fragmentShaderFile(fShaderFile);
        std::stringstream vShaderStream, fShaderStream;

        // Read file's buffer contents into streams
        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();

        // Close file handlers
        vertexShaderFile.close();
        fragmentShaderFile.close();

        // Convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();

        // If geometry shader path is present, also load a geometry shader
        if (gShaderFile != nullptr)
        {
            std::ifstream geometryShaderFile(gShaderFile);
            std::stringstream gShaderStream;
            gShaderStream << geometryShaderFile.rdbuf();
            geometryShaderFile.close();
            geometryCode = gShaderStream.str();
        }
    }
    catch (std::exception e)
    {
        // Raise error
        std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    const char* gShaderCode = geometryCode.c_str();
    
    // Create shader object from source code
    Shader shader;
    shader.Compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);
    
    return shader;
}

Texture2D Resources::LoadTextureFromFile(const char* file, bool alpha)
{
    // Create texture object
    Texture2D texture;
    
    if (alpha)
    {
        texture.Internal_Format = GL_RGBA;
        texture.Image_Format = GL_RGBA;
    }

    // load image
    int width, height, nrChannels;
    unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);
    // now generate texture
    texture.Generate(width, height, data);
    // and finally free image data
    stbi_image_free(data);
    return texture;
}