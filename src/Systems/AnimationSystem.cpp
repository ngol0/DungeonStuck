#include "AnimationSystem.h"

#include "../Components/SpriteComponent.h"
#include "../Components/AnimationComponent.h"
#include "../ECS/ECS.h"

AnimationSystem::AnimationSystem()
{
    RequireComponent<SpriteComponent>();
    RequireComponent<AnimationComponent>();
}

void AnimationSystem::Update(float dt)
{
    //update the transform
    for (auto& e : GetSystemEntities())
    {
        auto& sprite = e.GetComponent<SpriteComponent>();
        auto& animation = e.GetComponent<AnimationComponent>();

        animation.currentFrame++;
        auto animationFrameIndex = (animation.currentFrame / animation.frameSpeed) % animation.numOfFrame;
        auto frameWidth = sprite.width / animation.numOfFrame;

        //display correct sprite in this frame
        sprite.srcRect.x = frameWidth * animationFrameIndex;
        sprite.srcRect.w = frameWidth;
    }
}