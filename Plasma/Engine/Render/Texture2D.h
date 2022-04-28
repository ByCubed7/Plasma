// By @ByCubed7 on Twitter

#pragma once

#include "../Resource.h"

// Texture2D is able to store and configure a texture in OpenGL.
// It also hosts utility functions for easy management.
class Texture2D : public Resource<Texture2D>
{
public:
    unsigned int id;
    unsigned int width, height; 
    
    // Format of texture object and loaded image
    unsigned int internalFormat, imageFormat;

    // Wrapping mode on S and T axis
    unsigned int wrapS, wrapT;

    // Filtering mode if texture pixels </> screen pixels
    unsigned int filterMin, filterMax;
    
    // Default Constructor
    Texture2D();

    // Generates texture from image data
    void Generate(unsigned int width, unsigned int height, unsigned char* data);
    
    // Binds the texture as the current active GL_TEXTURE_2D texture object
    void Bind() const;

    // - 

protected:
    Texture2D* FromFile(const std::string filename) override;
    void Clear() override;
};
