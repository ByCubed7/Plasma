#include <iostream>
#include <sstream>
#include <fstream>

#include "../Library/stb_image.h"
#include "../Library/glad.h"

#include <GLFW/glfw3.h>

#include "Resources.h"
#include "Font.h"

#include <map>
#include <iostream>

#include <ft2build.h>
#include FT_FREETYPE_H  

using namespace std;


// Cache any resources we load
std::map<std::string, Texture2D> Resources::Textures;
std::map<std::string, Shader> Resources::Shaders;
std::map<std::string, Font> Resources::Fonts;

unsigned int Resources::defaultFontSize = 24;

// Shader

Shader Resources::LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name)
{
    Shaders[name] = LoadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
    return Shaders[name];
}

Shader& Resources::GetShader(std::string name) { return Shaders[name]; }


// Texture

Texture2D Resources::LoadTexture(const char* file, bool alpha, std::string name)
{
    Textures[name] = LoadTextureFromFile(file, alpha);
    return Textures[name];
}

Texture2D& Resources::GetTexture(std::string name) { return Textures[name]; }


// Font

Font Resources::LoadFont(const char* file, std::string name)
{
    Fonts[name] = LoadFontFromFile(file, defaultFontSize);
    return Fonts[name];
}

Font& Resources::GetFont(std::string name) { return Fonts[name]; }


//

void Resources::Clear()
{
    // Delete all the shaders and textures
    for (auto iter : Shaders) glDeleteProgram(iter.second.Program);
    for (auto iter : Textures) glDeleteTextures(1, &iter.second.ID);
}

//

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

    // Load
    int width, height, nrChannels;
    unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);

    // Generate texture
    texture.Generate(width, height, data);
    
    // Free image data
    stbi_image_free(data);
    return texture;
}


Font Resources::LoadFontFromFile(const char* file, unsigned int size) 
{
    cout << "loading font from file \n";

    FT_Library ft;
    if (FT_Init_FreeType(&ft))
    {
        std::cout << "ERROR: Could not init FreeType Library" << std::endl;
        //return -1;
    }

    FT_Face face;
    if (FT_New_Face(ft, file, 0, &face))
    {
        std::cout << "ERROR: Failed to load font" << std::endl;
        //return -1;
    }


    FT_Set_Pixel_Sizes(face, 0, defaultFontSize);
    
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

    Font newFont = Font();

    for (unsigned char c = 0; c < 128; c++) // Only do 128 characters~
    {
        // Load glyph 
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR: Failed to load Glyph" << std::endl;
            continue;
        }

        // Generate texture
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );

        // Set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Create Character
        Character character = {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            face->glyph->advance.x
        };

        // Store character
        //newFont.AddCharacter(c, character);
        newFont.Characters[c] = character;
    }
    // Clear FreeType's resources
    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    return newFont;
}