// By @ByCubed7 on Twitter

#pragma once

#include "Resource.h"
#include "Shader.h"

#include <string>

// █▀ █ █ ▄▀█ █▀▄ █▀▀ █▀█
// ▄█ █▀█ █▀█ █▄▀ ██▄ █▀▄

class ShaderResource : public Resource<Shader> 
{
	static Shader Load(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name) {
		cache[name] = LoadFromFile(vShaderFile, fShaderFile, gShaderFile);
		return cache[name];
	}

private:
    static Shader LoadFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile)
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
        const char* gShaderCode = geometryCode.c_str(); // <-- Could raise a bug in the future

        // Create shader object from source code
        Shader shader;
        shader.Compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);

        return shader;
	}
};
