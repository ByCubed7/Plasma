// By @ByCubed7 on Twitter


//#define VERBOSE

#include "Font.h"

#include <ft2build.h>
#include <freetype.h>  

unsigned int Font::defaultFontSize = 24;

void Font::AddCharacter(char c, Character character)
{
    Characters[c] = character;
}

Character Font::GetCharacter(char c) 
{
    return Characters[c];
}

Font Font::FromFile(const std::string filename)
{
    FT_Library ft;
    if (FT_Init_FreeType(&ft))
        std::cout << "ERROR: Could not init FreeType Library" << std::endl;
    
    FT_Face face;
    if (FT_New_Face(ft, filename.c_str(), 0, &face))
        std::cout << "ERROR: Failed to load font" << std::endl;


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
            (unsigned int) face->glyph->advance.x
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

void Font::Clear()
{
}
//
//void Font::LoadRenderer()
//{
//#ifdef VERBOSE
//    std::cout << "[TextRenderer::Ctor]\n\t - Created TextRenderer" << std::endl;
//#endif
//
//    // Configure VBO for texture quads
//    glBindVertexArray(vertexArrayObject);
//
//    glGenBuffers(1, &verticeVBO);
//    glBindBuffer(GL_ARRAY_BUFFER, verticeVBO);
//#ifdef VERBOSE
//    std::cout << "\t - Binded Vertice Buffer Object: " << verticeVBO << std::endl;
//#endif
//
//    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
//
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
//
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//    glBindVertexArray(0);
//}
//
//void Font::UnloadRenderer()
//{
//}
//
//void Font::Render(std::string text, glm::vec2 position, glm::vec2 size, glm::vec2 pivot, float rotate, int frame, glm::vec3 color)
//{
//#ifdef VERBOSE
//    std::cout << "[TextRenderer::RenderText]" << std::endl;
//    std::cout << "\t - Attempting to render: " << text << std::endl;
//#endif
//
//    // Get Font from resources
//    Font font = Font::Get("arial");
//
//    // Activate corresponding render state	
//    this->shader.Use();
//    this->shader.SetVector3f("textColor", color);
//
//    glActiveTexture(GL_TEXTURE0);
//    this->shader.SetInteger("text", 0);
//
//    glBindVertexArray(vertexArrayObject);
//
//    // Calcualte total texture size for pivoting
//    float width = 0;
//    float height = 0;
//    std::string::const_iterator c;
//    for (c = text.begin(); c != text.end(); c++)
//    {
//        //Character ch = Characters[*c];
//        Character ch = font.Characters[*c];
//        //Character ch = font.GetCharacter(*c);
//
//        width += ch.Size.x * scale;
//        height = std::max(height, ch.Size.y * scale);
//    }
//
//    // Iterate through all characters
//    for (c = text.begin(); c != text.end(); c++)
//    {
//        //Character ch = Characters[*c];
//        Character ch = font.Characters[*c];;
//
//        float xpos = x + ch.Bearing.x * scale;
//        float ypos = y + (font.Characters['H'].Bearing.y - ch.Bearing.y) * scale;
//
//        // Apply pivot
//        xpos -= (width * pivot.x);
//        ypos -= (height * pivot.y);
//
//        float w = ch.Size.x * scale;
//        float h = ch.Size.y * scale;
//
//        // Update VBO
//        float vertices[6][4] = {
//            { xpos,     ypos + h,   0.0f, 1.0f },
//            { xpos + w, ypos,       1.0f, 0.0f },
//            { xpos,     ypos,       0.0f, 0.0f },
//
//            { xpos,     ypos + h,   0.0f, 1.0f },
//            { xpos + w, ypos + h,   1.0f, 1.0f },
//            { xpos + w, ypos,       1.0f, 0.0f }
//        };
//
//        // Render glyph texture over quad
//        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
//        glBindBuffer(GL_ARRAY_BUFFER, verticeVBO); // Update VBO memory content
//        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Use glBufferSubData and not glBufferData
//        glBindBuffer(GL_ARRAY_BUFFER, 0);
//        glDrawArrays(GL_TRIANGLES, 0, 6); // Render quad
//
//        // Advance cursors for next glyph
//        x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (1/64th times 2^6 = 64)
//    }
//
//    glBindTexture(GL_TEXTURE_2D, 0);
//    glBindVertexArray(0);
//}
