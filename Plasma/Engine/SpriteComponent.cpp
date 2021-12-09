// By @ByCubed7 on Twitter

#include "SpriteComponent.h"

#include "Component.h"
#include "Settings.h"

SpriteComponent::SpriteComponent(std::string name)
    : Component(name)
{
    color = { 1, 1, 1 };

    animationPoint = 0;
    animationSpeed = 0;

	sprite = Texture2D();
	spriteFrame = 0;
	spriteSize = 1024;

    bounds = AABB();
}

void SpriteComponent::Draw(Render::Renderers& renderer)
{
    int ppu = gameObject->scene->settings.PPU;

    renderer.sprite.DrawSprite(
        this->sprite,
        { gameObject->position.x, gameObject->position.y },
        { gameObject->scale.x * ppu, gameObject->scale.y * ppu },
        gameObject->rotation,
        spriteFrame,
        color
    );
}

void SpriteComponent::Update(double delta, Engine::Scene& game)
{
    animationPoint += delta;
    spriteFrame = animationPoint * animationSpeed;
}

AABB SpriteComponent::GetBounds() { return bounds; }

// Update bounds
void SpriteComponent::CalcBounds() 
{
    int ppu = gameObject->scene->settings.PPU;
    Vector2 upperBound = Vector2(ppu) / 2;
    Vector2 lowerBound = Vector2(-ppu) / 2;
    this->bounds = AABB(lowerBound, upperBound);
}

SpriteComponent* SpriteComponent::Set(Texture2D sprite) { this->sprite = sprite; return this; }
Texture2D SpriteComponent::Get() { return this->sprite; }

SpriteComponent* SpriteComponent::AnimationSpeed(double speed) { this->animationSpeed = speed; return this; }
int SpriteComponent::GetAnimationSpeed() { return this->animationSpeed; }

