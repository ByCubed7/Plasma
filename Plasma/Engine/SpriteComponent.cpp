#include "SpriteComponent.h"

#include "Component.h"

SpriteComponent::SpriteComponent(GameObject* gameObject, std::string name)
    : Component(gameObject, name)
{
    color = { 1, 1, 1 };

	sprite = Texture2D();
	spriteFrame = 0;
	spriteSize = 1024;

    bounds = AABB();
}

void SpriteComponent::Draw(Renderer& renderer)
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
        color
    );

    //cout << "SpriteComponent::Draw.Renderer:" << &renderer << endl;
    cout << "this->sprite:" << &this->sprite << endl;

}

AABB SpriteComponent::GetBounds() { return bounds; }

// Update bounds
void SpriteComponent::CalcBounds() 
{
    Vector2 upperBound = Vector2(Settings::PPU, Settings::PPU) / 2;
    Vector2 lowerBound = Vector2(-Settings::PPU, -Settings::PPU) / 2;
    this->bounds = AABB(lowerBound, upperBound);
}

SpriteComponent* SpriteComponent::Set(Texture2D sprite) { this->sprite = sprite; return this; }
Texture2D SpriteComponent::Get() { return this->sprite; }

