#ifndef PLAYERINPUTSYSTEM_H
#define PLAYERINPUTSYSTEM_H

#include "../../ECS/ECS.h"
#include "../../Input/InputData.h"

#include <glm/glm.hpp>

//------------------------------------------------------//
//-----------------Player Input System--------------------
//Responsible for:
//- Binding and defining default input
//- Rebinding input if user needs
//------------------------------------------------------//

class PlayerInputSystem : public System
{
private:
    

public:
    PlayerInputSystem();

    void Init() override;
    void Update(float dt) override {};

    void ConfigureDefaultInputBindings();
};

#endif