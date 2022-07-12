#pragma once

#include "../GameObject.h"
#include "../Component.h"
#include "../Render/Texture2D.h"
#include "../Render/Animation.h"

namespace Engine
{
    template<typename States, typename Actions>
    class AnimatedSprite : public Component
    {
    public:
        Render::Animation<States, Actions> animation;

        AnimatedSprite(GameObject* owner, States startState) : Component(owner), animation(startState)
        {
        }

        //void Draw(SDL_Renderer* renderer) override;
        void Update(double time, double delta, Engine::Scene& game) override
        {
            //Vector2Int offset = animation.Get();
            //SDL_Rect& area = sprite->Source();
            //area.x = offset.X();
            //area.y = offset.Y();
            //area.w = animation.size.X();
            //area.h = animation.size.Y();

            //std::cout << "Size: " << animation.size << std::endl;
            animation.Tick();
        }

        AnimatedSprite* SetSize(Vector2Int newSize) {
            animation.size = newSize;
            return this;
        }
    };
}


