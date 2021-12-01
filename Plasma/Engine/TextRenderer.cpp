// By @ByCubed7 on Twitter

#include <iostream>

#include <glm/gtc/matrix_transform.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "TextRenderer.h"
#include "Resources.h"

TextRenderer::TextRenderer(Shader& shader) 
    : Renderer(shader)
{    
    // Configure VBO for texture quads
    glBindVertexArray(vertexArrayObject);

    glGenBuffers(1, &verticeVBO);
    glBindBuffer(GL_ARRAY_BUFFER, verticeVBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

TextRenderer::~TextRenderer()
{
    glDeleteVertexArrays(1, &vertexArrayObject);
}

void TextRenderer::RenderText(std::string text, float x, float y, float scale, glm::vec2 pivot, glm::vec3 color)
{
    // Get Font from resources
    Font font = Resources::GetFont("arial");

    // Activate corresponding render state	
    this->shader.Use();
    this->shader.SetVector3f("textColor", color);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(vertexArrayObject);

    this->shader.SetInteger("text", 0);

    // Calcualte total texture size for pivoting
    float width = 0;
    float height = 0;
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        //Character ch = Characters[*c];
        Character ch = font.Characters[*c];
        //Character ch = font.GetCharacter(*c);

        width += ch.Size.x * scale;
        height += ch.Size.y * scale;
    }

    // Iterate through all characters
    for (c = text.begin(); c != text.end(); c++)
    {
        //Character ch = Characters[*c];
        Character ch = font.Characters[*c];;

        float xpos = x + ch.Bearing.x * scale;
        float ypos = y + (font.Characters['H'].Bearing.y - ch.Bearing.y) * scale;

        // Apply pivot
        xpos -= (width * pivot.x);
        ypos -= (height * pivot.y);

        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;
        
        // Update VBO
        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 0.0f },
            { xpos,     ypos,       0.0f, 0.0f },

            { xpos,     ypos + h,   0.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 0.0f }
        };
        
        // Render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        glBindBuffer(GL_ARRAY_BUFFER, verticeVBO); // Update VBO memory content
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Use glBufferSubData and not glBufferData
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDrawArrays(GL_TRIANGLES, 0, 6); // Render quad
        
        // Advance cursors for next glyph
        x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (1/64th times 2^6 = 64)
    }

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}