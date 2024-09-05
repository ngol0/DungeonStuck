#ifndef PLAYERMOVEMENTSYSTEM_H
#define PLAYERMOVEMENTSYSTEM_H

#include "../../ECS/ECS.h"
#include <glm/glm.hpp>
#include "../../Events/EventData.h"

class PlayerActionSystem : public System
{
private:
    void OnStartHitWall(CollisionData& data);
    void OnKeepHittingWall(CollisionData& data);
    void OnDoneHittingWall(CollisionData& data);

    void OnStartAttack(Entity& attacker);
    void OnEndAttack(Entity& attacker);

    void OnPlayerDie(Entity& victim);

    float m_moveVariable{1.f};
    float m_forceCount{0.f};
    float m_force{0.f};
    float m_initialForce{20.f};
    bool m_isAttacking;

public:
    PlayerActionSystem();

    void Init() override;
    void Move(glm::vec3& value, float dt = 0.f);

    void Update(float dt) override;
};

#endif