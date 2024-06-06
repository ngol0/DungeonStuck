#ifndef ECS_H
#define ECS_H

#include <bitset>
#include <vector>

inline std::size_t GetUniqueId()
{
    static std::size_t lastId{ 0u };
    return lastId++; //return the value first, then increment
}

template<typename T>
struct Component
{
    static int GetId()
    {
        //only got init once at first, will skip this line after the first call
        static std::size_t typeId = GetUniqueId(); 
        return typeId;
    }
};

class Entity
{
private:
    int m_id;

public:
    Entity(int id);
    int GetId() const { return m_id; }

    bool operator == (const Entity& other) const
    {
        return m_id == other.m_id;
    }
};

/////////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------//
//The system processes entities that contain a specific signature
//-----------------------------------------------------------------------------//
/////////////////////////////////////////////////////////////////////////////////

const unsigned int MAX_COMPONENTS = 32;
typedef std::bitset<MAX_COMPONENTS> Signature;

class System
{
private:
    // which components an entity must have for the system to consider the entity
    Signature m_component_signature;

    // list of all entities that a system is interested in
    std::vector<Entity> m_entities;

public:
    System() = default;
    ~System() = default;

    void AddEntityToSystem(const Entity& entity);
    void RemoveEntityFromSystem(const Entity& entity);

    const std::vector<Entity>& GetSystemEntities() const { return m_entities; }
    const Signature& GetComponentSignature() const { return m_component_signature; }

    // define the component type T that entities must have to be considered by the system
    template <typename TComponent> 
    void RequireComponent();
};

template <typename TComponent>
void System::RequireComponent()
{
    const auto typeId = Component<TComponent>::GetId(); 
    m_component_signature.set(typeId);
}

class Registry
{

};

#endif