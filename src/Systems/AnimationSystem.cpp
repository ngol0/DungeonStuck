#include "AnimationSystem.h"

#include "../Components/SpriteComponent.h"
#include "../Components/AnimationComponent.h"

#include "../Events/EventManager.h"
#include "../Events/EventType.h"

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

        auto frameWidth = sprite.width / animation.numOfFrame;
        auto frameHeight = sprite.height / animation.numOfAnims;

        int lastAnim = animation.numOfFrame - 1;

        int animationFrameIndex = 0;

        if (animation.endOfSprite && !animation.isLooping)
        {
            animationFrameIndex = lastAnim;
            animation.currentFrame = 0;

            //send an event
            EventManager::GetInstance().Notify<Entity>(EventType::OnDoneAnim, e);
        }
        else
        {
            animation.currentFrame++;
            animationFrameIndex = (animation.currentFrame / animation.frameSpeed) % animation.numOfFrame;

            if (animationFrameIndex == lastAnim)
            {
                animation.endOfSprite = true;
            }
        }

        sprite.srcRect.x = frameWidth * animationFrameIndex;
        
        sprite.srcRect.w = frameWidth;
        sprite.srcRect.h = frameHeight;        
    }
}