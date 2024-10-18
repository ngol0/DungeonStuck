#include "HealthUISystem.h"


#include "../../Components/HealthUIComponent.h"
#include "../../Components/SpriteComponent.h"
#include "../../Components/TextComponent.h"

#include "../../Events/EventManager.h"
#include "../../Events/EventType.h"

HealthUISystem::HealthUISystem()
{
    RequireComponent<HealthUIComponent>();
    RequireComponent<UIComponent>();
    RequireComponent<TextComponent>();
}

void HealthUISystem::Init()
{
    EventManager::GetInstance().Register<HealthData>(EventType::OnHealthChanged, this, &HealthUISystem::OnPlayerHealed);
}

void HealthUISystem::OnPlayerHealed(HealthData& data)
{
    for (auto &e : GetSystemEntities())
    {
        auto &healthLabel = e.GetComponent<TextComponent>();
        healthLabel.text = std::to_string(data.curData/100) + "/3";
    }
}