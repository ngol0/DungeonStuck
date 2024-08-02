#include "ECS.h"

//-------Entity-----------------//
Entity::Entity(int id) : m_id(id)
{   

}

void Entity::Destroy()
{
    Registry::GetInstance().KillEntity(*this);
}


//-------------System-------------//
void System::AddEntityToSystem(const Entity& entity)
{
    m_entities.push_back(entity);
}

void System::RemoveEntityFromSystem(const Entity& entity)
{
    auto iter = std::remove_if(m_entities.begin(), m_entities.end(), 
        [&](const Entity& other) { return other == entity; });
    m_entities.erase(iter, m_entities.end());
}

//--------------Registry------------//
Registry::~Registry()
{
    for (auto& pair : m_systems)
    {
        delete pair.second;
    }

    for (auto& pool : m_componentPools)
    {
        delete pool;
    }
}

void Registry::Update(float dt)
{
    //add entity
    for (const auto& e : m_entitesToBeAdded)
    {
        AddEntityToSystem(e);
    }
    m_entitesToBeAdded.clear();

    //todo: remove entity
    for (const auto& e : m_entitiesToBeRemoved)
    {
        RemoveEntityFromSystem(e);
    }
    m_entitiesToBeRemoved.clear();
    
    //update all systems
    for (const auto& pair : m_systems)
    {
        pair.second->Update(dt);
    }
}

void Registry::Render(SDL_Renderer* renderer)
{
    for (const auto& pair : m_systems)
    {
        pair.second->Render(renderer);
    }
}

Entity Registry::CreateEntity()
{
    auto id = m_numberOfEntitnes++;
    Entity e(id);

    //call resize > a bitmask is created using default constructor
    if (id >= m_entityComponentSignatures.size())
    {
        m_entityComponentSignatures.resize(id + 1);
    }

    //spdlog::info("Entity Created with id: " + std::to_string(id));

    m_entitesToBeAdded.insert(e);

    return e;
}

void Registry::KillEntity(const Entity& entity)
{
    m_entitiesToBeRemoved.insert(entity);
}

void Registry::AddEntityToSystem(const Entity& entity)
{
    const auto entityId = entity.GetId();

    //get entity component signature
    const Signature& entityComponentSignature = m_entityComponentSignatures[entityId];
    
    //loop through all systems and get each system signature
    for (const auto& pair : m_systems)
    {
        const Signature& systemSignature = pair.second->GetComponentSignature();

        bool isInterested = (systemSignature & entityComponentSignature) == systemSignature;

        if (isInterested)
        {
            pair.second->AddEntityToSystem(entity);
        }
    }
}

void Registry::RemoveEntityFromSystem(const Entity& entity)
{
    for (const auto& pair : m_systems)
    {
        //remove from system
        pair.second->RemoveEntityFromSystem(entity);

        //reset signature
        m_entityComponentSignatures[entity.GetId()].reset();
    }
}

Registry& Registry::GetInstance()
{
	static Registry registry;
	return registry;
}