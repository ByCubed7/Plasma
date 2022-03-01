// By @ByCubed7 on Twitter

#include "All.h"
//#define VERBOSE

#include "SpriteComponent.h"

#include "../GameObject.h"
#include "../Component.h"
#include "../Vector2.h"
#include "../Window.h"

SpriteComponent::SpriteComponent(Engine::GameObject* gameObject, std::string name)
    : Component(gameObject, name)
{
    color = { 1, 1, 1 };

    animationPoint = 0;
    animationSpeed = 0;

	sprite = Texture2D();
	spriteFrame = 0;
	spriteSize = 1024;

    pivot = { 0.5, 0.5 };

    bounds = AABB();
}

void SpriteComponent::Draw(Render::Renderers& renderer)
{
    int ppu = gameObject->scene->GetWindow()->GetPPU();

    renderer.sprite.DrawSprite(
        this->sprite,
        { gameObject->position.x, gameObject->position.y },
        { gameObject->scale.x * ppu, gameObject->scale.y * ppu },
        { pivot.x, pivot.y },
        gameObject->rotation,
        spriteFrame,
        glm::vec3(color.red / 255, color.blue / 255, color.green / 255)
    );
}

void SpriteComponent::Update(double delta, Engine::Scene& game)
{
    animationPoint += delta;
    spriteFrame = (int) animationPoint * animationSpeed;
}

AABB SpriteComponent::GetBounds() { return bounds; }

// Update bounds
void SpriteComponent::CalcBounds() 
{
    int ppu = gameObject->scene->GetWindow()->GetPPU();
    Vector2 upperBound = Vector2(ppu) / 2;
    Vector2 lowerBound = Vector2(-ppu) / 2;
    this->bounds = AABB(lowerBound, upperBound);
}

SpriteComponent* SpriteComponent::Set(Texture2D sprite) { this->sprite = sprite; return this; }
Texture2D SpriteComponent::Get() { return this->sprite; }

SpriteComponent* SpriteComponent::AnimationSpeed(double speed) { this->animationSpeed = speed; return this; }
SpriteComponent* SpriteComponent::SetColour(Colour newColour) { color = newColour; return this; }
int SpriteComponent::GetAnimationSpeed() { return this->animationSpeed; }
