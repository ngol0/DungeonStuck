#ifndef INTERACTSYSTEM_H
#define INTERACTSYSTEM_H

#include "../../ECS/ECS.h"
#include "../../Events/EventData.h"

class ItemCollectSystem : public System
{
private:

public:
    ItemCollectSystem();

    void Init() override;
    void Update(float dt) override;

    void CollectItem(int& data);
    void OnNearItem(CollisionData& data);
    void OnExitItem(CollisionData& data);

    Entity FindItem(CollisionData& data);
};

#endif

