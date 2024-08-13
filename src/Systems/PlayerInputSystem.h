#ifndef PLAYERINPUTSYSTEM_H
#define PLAYERINPUTSYSTEM_H

#include "../ECS/ECS.h"

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

    //todo: implement this
    //void RebindInput();
};

#endif