// By @ByCubed7 on Twitter


//#define VERBOSE

#include "Texture2D.h"

#include <iostream>

#include "OpenGL.h"
#include <lodepng.h>


Texture2D::Texture2D() : size(0), internalFormat(GL_RGB), imageFormat(GL_RGB), wrapS(GL_REPEAT), wrapT(GL_REPEAT), filterMin(GL_NEAREST), filterMax(GL_NEAREST)
{
    glGenTextures(1, &id);
}

void Texture2D::generate(unsigned int width, unsigned int height, unsigned char* data)
{
    this->size.x = width;
    this->size.y = height;

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

void Texture2D::bind() const
{
    glBindTexture(GL_TEXTURE_2D, id);
}

Texture2D Texture2D::FromFile(const std::string filename)
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

    std::vector<unsigned char> data = std::vector<unsigned char>();
    unsigned width, height;
    unsigned error = lodepng::decode(data, width, height, filename);
    //std::cout << lodepng_error_text(error) << std::endl;

    // Generate texture
    generate(width, height, &data[0]);

    // Free image data
    //stbi_image_free(data);
    return *this;
}

void Texture2D::Clear()
{
    glDeleteTextures(1, &id);
}

void Texture2D::LoadRenderer()
{
    float vertices[] = {
        // pos      // tex
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };

    glBindVertexArray(vertexArrayObject);

    glGenBuffers(1, &verticeVBO);

    glBindBuffer(GL_ARRAY_BUFFER, verticeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Texture2D::UnloadRenderer()
{

}

void Texture2D::Render(glm::vec2 position, glm::vec2 size, glm::vec2 scale, glm::vec2 pivot, float rotate, glm::vec2 crop, glm::vec3 color)
{
    // Prepare transformations
    shader.Use();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position - scale * pivot, 0.0f)); // translate
    model = glm::translate(model, glm::vec3(0.5f * scale.x, 0.5f * scale.y, 0.0f)); // move origin of rotation to center of quad
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f)); // rotate
    model = glm::translate(model, glm::vec3(-0.5f * scale.x, -0.5f * scale.y, 0.0f)); // move origin back
    model = glm::scale(model, glm::vec3(scale, 1.0f)); // scale

    shader.SetMatrix4("model", model);

    // render textured quad
    shader.SetVector3f("spriteColor", color);

    // Set shadow render dims
    shader.SetVector2f("size", { size.x, size.y });

    // Texture crop
    shader.SetVector2f("crop", { crop.x, crop.y });

    glActiveTexture(GL_TEXTURE0);
    bind();

    glBindVertexArray(vertexArrayObject);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
