#ifndef PLAYERACTIONSYSTEM_H
#define PLAYERACTIONSYSTEM_H

#include "../../ECS/ECS.h"
#include <glm/glm.hpp>
#include "../../Events/EventData.h"

class PlayerActionSystem : public System
{
private:
    void OnStartHitWall(CollisionEventData& data);
    void OnKeepHittingWall(CollisionEventData& data);
    void OnDoneHittingWall(CollisionEventData& data);

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