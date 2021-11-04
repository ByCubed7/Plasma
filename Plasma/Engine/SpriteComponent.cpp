#include "SpriteComponent.h"

#include "Component.h"

SpriteComponent::SpriteComponent(GameObject* gameObject, std::string name)
    : Component(gameObject, name)
{
	sprite = Texture2D();
	spriteFrame = 0;
	spriteSize = 0;

    bounds = AABB();
}

void SpriteComponent::Draw(Renderer renderer)
{
    int PPU(Settings::PPU);
    glm::vec2 drawScale = { gameObject->scale.x * PPU, gameObject->scale.y * PPU };
    glm::vec2 pos = { gameObject->position.x, gameObject->position.y };

    renderer.DrawSprite(
        this->sprite,
        pos,
        drawScale,
        gameObject->rotation,
        spriteFrame,
        gameObject->color
    );
}

AABB SpriteComponent::GetBounds() { return bounds; }

// Update bounds
void SpriteComponent::CalcBounds() 
{
    Vector2 upperBound = Vector2(Settings::PPU, Settings::PPU) / 2;
    Vector2 lowerBound = Vector2(-Settings::PPU, -Settings::PPU) / 2;
    this->bounds = AABB(lowerBound, upperBound);
}

void SpriteComponent::Set(Texture2D sprite) { this->sprite = sprite; }
Texture2D SpriteComponent::Get() { return this->sprite; }

