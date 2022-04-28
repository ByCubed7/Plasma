// By @ByCubed7 on Twitter

#include "All.h"
//#define VERBOSE

#include "Texture2D.h"

#include <iostream>
#include <lodepng.h>

Texture2D::Texture2D() : width(0), height(0), internalFormat(GL_RGB), imageFormat(GL_RGB), wrapS(GL_REPEAT), wrapT(GL_REPEAT), filterMin(GL_NEAREST), filterMax(GL_NEAREST)
{
    glGenTextures(1, &id);
}

void Texture2D::Generate(unsigned int width, unsigned int height, unsigned char* data)
{
    this->width = width;
    this->height = height;

    // Bind Texture
    glBindTexture(GL_TEXTURE_2D, id);
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, imageFormat, GL_UNSIGNED_BYTE, data);
    
    // Set Texture wrap and filter modes
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMin);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMax);
    
    // Unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::Bind() const
{
    glBindTexture(GL_TEXTURE_2D, id);
}

Texture2D* Texture2D::FromFile(const std::string filename)
{
    bool alpha = true;

    // Create texture object
    //Texture2D texture;

    if (alpha)
    {
        internalFormat = GL_RGBA;
        imageFormat = GL_RGBA;
    }

    // Load
    //int width, height, nrChannels;
    //unsigned char* data = stbi_load(file.c_str(), &width, &height, &nrChannels, 0);

    std::vector<unsigned char> data;
    unsigned width, height;
    unsigned error = lodepng::decode(data, width, height, filename);


    // Generate texture
    Generate(width, height, &data[0]);

    // Free image data
    //stbi_image_free(data);
    return this;
}

void Texture2D::Clear()
{
    glDeleteTextures(1, &id);
}
