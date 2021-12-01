// By @ByCubed7 on Twitter

#include "SpriteComponent.h"

#include "Component.h"

SpriteComponent::SpriteComponent(GameObject* gameObject, std::string name)
    : Component(gameObject, name)
{
    color = { 1, 1, 1 };

    animationPoint = 0;
    animationSpeed = 0;

	sprite = Texture2D();
	spriteFrame = 0;
	spriteSize = 1024;

    bounds = AABB();
}

void SpriteComponent::Draw(Renderers& renderer)
{
    int PPU(Settings::PPU);
    glm::vec2 drawScale = { gameObject->scale.x * PPU, gameObject->scale.y * PPU };
    glm::vec2 pos = { gameObject->position.x, gameObject->position.y };

    renderer.sprite.DrawSprite(
        this->sprite,
        pos,
        drawScale,
        gameObject->rotation,
        spriteFrame,
        color
    );
}

void SpriteComponent::Update(double delta, Game& game) 
{
    animationPoint += delta;
    spriteFrame = animationPoint * animationSpeed;
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

SpriteComponent* SpriteComponent::AnimationSpeed(double speed) { this->animationSpeed = speed; return this; }
int SpriteComponent::GetAnimationSpeed() { return this->animationSpeed; }

