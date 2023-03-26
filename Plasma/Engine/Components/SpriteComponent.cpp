// By @ByCubed7 on Twitter


//#define VERBOSE

#include "SpriteComponent.h"

#include "../Scene.h"
#include "../Render/Renderers.h"
#include "../GameObject.h"
#include "../Vector.h"
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

    bounds = AABB();
    crop = 0;
    size = 64;
}

void SpriteComponent::Draw(Render::Renderers& renderer)
{
    //std::cout << "Draw!" << std::endl;

    Vector2 scale = gameObject->scale;

    if (reflectionX) scale.x = -scale.x;
    if (reflectionY) scale.y = -scale.y;

    //renderer.sprite.DrawSprite(
    //    this->sprite,
    //    { gameObject->position.x, gameObject->position.y },
    //    { gameObject->scale.x * ppu, gameObject->scale.y * ppu },
    //    { pivot.x, pivot.y },
    //    gameObject->rotation,
    //    spriteFrame,
    //    glm::vec3(color.x / 255.0f, color.y / 255.0f, color.z / 255.0f)
    //);

    sprite.Draw(
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

void SpriteComponent::Update(double time, double delta, Engine::Scene& game)
{

}

AABB SpriteComponent::GetBounds() { return bounds; }

// Update bounds
void SpriteComponent::CalcBounds() 
{
    Vector2 upperBound = 1;
    Vector2 lowerBound = -1;
    this->bounds = AABB(lowerBound, upperBound);
}

SpriteComponent* SpriteComponent::setTexture2D(Texture2D newSprite) {
    sprite = newSprite;
    size = sprite.size;
    return this; 
}
Texture2D SpriteComponent::Get() { return sprite; }

SpriteComponent* SpriteComponent::SetColour(Colour4 newColour) { color = newColour; return this; }

