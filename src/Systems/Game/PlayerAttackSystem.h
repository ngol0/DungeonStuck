#ifndef PLAYERCOMBATSYSTEM_H
#define PLAYERCOMBATSYSTEM_H

#include "../../ECS/ECS.h"
#include "../../Events/EventData.h"

#include <glm/glm.hpp>


class PlayerAttackSystem : public System
{
public:
    PlayerAttackSystem();

    void Init() override;
    void Update(float dt) override;

    void Attack(AttackData& data);
};

#endif