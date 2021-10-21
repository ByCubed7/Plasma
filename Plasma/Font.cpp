#include "Font.h"

void Font::AddCharacter(char c, Character character)
{
    Characters.insert(std::pair<char, Character>(c, character));
}

Character Font::GetCharacter(char c) 
{
    return Characters[c];
}