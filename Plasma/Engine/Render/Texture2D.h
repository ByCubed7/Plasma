// By @ByCubed7 on Twitter

#pragma once

// Texture2D is able to store and configure a texture in OpenGL.
// It also hosts utility functions for easy management.
class Texture2D
{
public:
    // The ID of the texture object
    unsigned int ID;
    
    // The image dimensions, in pixels
    unsigned int Width, Height; 
    
    // - Texture Format

    // Format of texture object
    unsigned int Internal_Format;

    // Format of loaded image
    unsigned int Image_Format; 
    
    // - Configuration

    // Wrapping mode on S axis
    unsigned int Wrap_S; 

    // wrapping mode on T axis
    unsigned int Wrap_T; 

    // Filtering mode if texture pixels < screen pixels
    unsigned int Filter_Min; 

    // Filtering mode if texture pixels > screen pixels
    unsigned int Filter_Max; 
    
    // Default Constructor
    Texture2D();

    // Generates texture from image data
    void Generate(unsigned int width, unsigned int height, unsigned char* data);
    
    // Binds the texture as the current active GL_TEXTURE_2D texture object
    void Bind() const;
};
