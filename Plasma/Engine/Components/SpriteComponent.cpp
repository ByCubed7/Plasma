// By @ByCubed7 on Twitter


//#define VERBOSE

#include "SpriteComponent.h"

#include "../GameObject.h"
#include "../Component.h"
#include "../Vector.h"
#include "../Window.h"

#include "../Render/Renderers.h"

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
    //std::cout << "Draw!" << std::endl;

    //color = RGBA({
    //    (unsigned char)(rand() % 255),
    //    (unsigned char)(rand() % 255),
    //    (unsigned char)(rand() % 255)
    //});
    //color.w = 255;

    int ppu = gameObject->scene->GetWindow()->GetPPU();

    renderer.sprite.DrawSprite(
        this->sprite,
        { gameObject->position.x, gameObject->position.y },
        { gameObject->scale.x * ppu, gameObject->scale.y * ppu },
        { pivot.x, pivot.y },
        gameObject->rotation,
        spriteFrame,
        glm::vec3(color.x / 255.0f, color.y / 255.0f, color.z / 255.0f)
    );
}

void SpriteComponent::Update(double time, double delta, Engine::Scene& game)
{
    //std::cout << "Update!" << std::endl;

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

SpriteComponent* SpriteComponent::AnimationSpeed(int speed) { this->animationSpeed = speed; return this; }
SpriteComponent* SpriteComponent::SetColour(RGBA newColour) { color = newColour; return this; }
int SpriteComponent::GetAnimationSpeed() { return this->animationSpeed; }

