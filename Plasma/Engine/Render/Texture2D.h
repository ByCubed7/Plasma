// By @ByCubed7 on Twitter

#pragma once

#include "../Resource.h"
#include "Renderable.h"


// Texture2D is able to store and configure a texture in OpenGL.
// It also hosts utility functions for easy management.
class Texture2D : public Resource<Texture2D>, public Renderable<Texture2D>
{
public:
    unsigned int id;
    Vector2Int size;
    
    // Format of texture object and loaded image
    unsigned int internalFormat, imageFormat;

    // Wrapping mode on S and T axis
    unsigned int wrapS, wrapT;

    // Filtering mode if texture pixels </> screen pixels
    unsigned int filterMin, filterMax;
    
    // Default Constructor
    Texture2D();

    // Generates texture from image data
    void generate(unsigned int width, unsigned int height, unsigned char* data);
    
    // Binds the texture as the current active GL_TEXTURE_2D texture object
    void bind() const;

protected:

    // Resource
    Texture2D FromFile(const std::string filename) override;
    void Clear() override;

    // Renderable
    unsigned int verticeVBO;
    void LoadRenderer() override;
    void UnloadRenderer() override;

    void Render(glm::vec2 position, glm::vec2 size, glm::vec2 scale, glm::vec2 pivot, float rotate, glm::vec2 crop, glm::vec3 color) override;
};
