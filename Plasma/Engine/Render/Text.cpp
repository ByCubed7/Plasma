#include "Text.h"
#include "Font.h"

#include <iostream>

#define VERBOSE

void Text::LoadRenderer()
{
#ifdef VERBOSE
    std::cout << "[TextRenderer::Ctor]\n\t - Created TextRenderer" << std::endl;
#endif

    // Configure VBO for texture quads
    glBindVertexArray(vertexArrayObject);

    glGenBuffers(1, &verticeVBO);
    glBindBuffer(GL_ARRAY_BUFFER, verticeVBO);
#ifdef VERBOSE
    std::cout << "\t - Binded Vertice Buffer Object: " << verticeVBO << std::endl;
#endif

    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Text::UnloadRenderer()
{
}

void Text::Render(glm::vec2 position, glm::vec2 size, glm::vec2 pivot, float rotate, int frame, glm::vec3 color)
{
#ifdef VERBOSE
    std::cout << "[TextRenderer::RenderText]" << std::endl;
    std::cout << "\t - Attempting to render: " << contents << std::endl;
#endif

    // Configure VBO for texture quads
    glBindVertexArray(vertexArrayObject);

    // Activate corresponding render state	
    shader.Use();
    shader.SetVector3f("textColor", color);

    glActiveTexture(GL_TEXTURE0);
    shader.SetInteger("text", 0);

    // Calcualte total texture size for pivoting
    float width = 0;
    float height = 0;
    std::string::const_iterator c;
    for (c = contents.begin(); c != contents.end(); c++)
    {
        //Character ch = Characters[*c];    
        Character ch = font.Characters[*c];
        //Character ch = font.GetCharacter(*c);

        width += ch.Size.x * size.x;
        height = std::max(height, ch.Size.y * size.y);
    }

    float cursorX = position.x;

    // Iterate through all characters
    for (c = contents.begin(); c != contents.end(); c++)
    {
        Character ch = font.Characters[*c];

        float xpos = cursorX + ch.Bearing.x * size.x;
        float ypos = position.y + (font.Characters['H'].Bearing.y - ch.Bearing.y) * size.y;

        // Apply pivot
        xpos -= (width * pivot.x);
        ypos -= (height * pivot.y);

        float w = ch.Size.x * size.x;
        float h = ch.Size.y * size.y;

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
        cursorX += (ch.Advance >> 6) * size.x; // bitshift by 6 to get value in pixels (1/64th times 2^6 = 64)
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
}
