// By @ByCubed7 on Twitter

#include "Font.h"

void Font::AddCharacter(char c, Character character)
{
    Characters[c] = character;
}

Character Font::GetCharacter(char c) 
{
    return Characters[c];
}