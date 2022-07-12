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
    color = { 255, 255, 255, 255 };

	sprite = Texture2D();
    reflection = { false, false };

    pivot = 0.5f;

    bounds = AABB();
    crop = 0;
    size = 64;
}

void SpriteComponent::Draw(Render::Renderers& renderer)
{
    //std::cout << "Draw!" << std::endl;

    int ppu = gameObject->scene->GetWindow()->GetPPU();

    Vector scale = gameObject->scale * ppu;

    if (reflection.x) scale.x = -scale.x;
    if (reflection.y) scale.y = -scale.y;

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
    int ppu = gameObject->scene->GetWindow()->GetPPU();
    Vector2 upperBound = Vector2(ppu) / 2;
    Vector2 lowerBound = Vector2(-ppu) / 2;
    this->bounds = AABB(lowerBound, upperBound);
}

SpriteComponent* SpriteComponent::Set(Texture2D newSprite) {
    size = sprite.size.Cast<unsigned int>();
    sprite = newSprite;
    return this; 
}
Texture2D SpriteComponent::Get() { return sprite; }

SpriteComponent* SpriteComponent::SetColour(RGBA newColour) { color = newColour; return this; }

