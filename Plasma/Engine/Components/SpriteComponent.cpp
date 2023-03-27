// By @ByCubed7 on Twitter


//#define VERBOSE

#include "SpriteComponent.h"

#include "../Scene.h"
#include "../Render/Renderers.h"
#include "../GameObject.h"
#include "../Vector.h"
#include "../Colour.h"
#include "../Window.h"

#include "OpenGL.h"

SpriteComponent::SpriteComponent(Engine::GameObject* gameObject, std::string name)
    : Component(gameObject, name)
{
    color = { 255, 255, 255, 255 };

	sprite = Texture2D();
    reflectionX = false;
    reflectionY = false;

    pivot = 0.5f;

    crop = 0;
    size = 64;
}

void SpriteComponent::draw(Render::Renderers& renderer)
{
    //std::cout << "Draw!" << std::endl;
    Vector2 scale = gameObject->scale;

    scale *= renderer.sprite.PPU;

    if (reflectionX) scale.x = -scale.x;
    if (reflectionY) scale.y = -scale.y;

    sprite.draw(
        sprite,
        gameObject->position,
        size,
        scale,
        pivot,
        gameObject->rotation,
        crop,
        color
    );
}

SpriteComponent* SpriteComponent::setTexture2D(Texture2D newSprite) {
    sprite = newSprite;
    return this; 
}

SpriteComponent* SpriteComponent::setColour(Colour4 newColour) { color = newColour; return this; }

