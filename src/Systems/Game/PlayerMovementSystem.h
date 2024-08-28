#ifndef PLAYERMOVEMENTSYSTEM_H
#define PLAYERMOVEMENTSYSTEM_H

#include "../../ECS/ECS.h"
#include <glm/glm.hpp>
#include "../../Events/EventData.h"

class PlayerMovementSystem : public System
{
private:
    void OnStartHit(CollisionData& data);
    void OnKeepHitting(CollisionData& data);
    void OnDoneHitting(CollisionData& data);

    float m_moveVariable{1.f};
    float m_forceCount{0.f};
    float m_force{0.f};
    float m_initialForce{20.f};

public:
    PlayerMovementSystem();

    void Init() override;
    void Move(glm::vec3& value, float dt = 0.f);

    void Update(float dt) override;
};

#endif