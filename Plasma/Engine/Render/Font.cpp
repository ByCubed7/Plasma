// By @ByCubed7 on Twitter

#include "All.h"
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

void Font::Clear()
{
}
