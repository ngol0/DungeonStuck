#ifndef ECS_H
#define ECS_H

#include <bitset>
#include <vector>
#include <unordered_map>
#include <typeindex>
#include <set>

inline std::size_t GetUniqueId()
{
    static std::size_t lastId{0u};
    return lastId++; // return the value first, then increment
}

template <typename T>
struct Component
{
    static int GetId()
    {
        // only got init once at first, will skip this line after the first call
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

    bool operator==(const Entity &other) const
    {
        return m_id == other.m_id;
    }
};

/////////////////////////////////////////////////////////////////////////////////
//--System
/////////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------//
// The system processes entities that contain a specific signature
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

    void AddEntityToSystem(const Entity &entity);
    void RemoveEntityFromSystem(const Entity &entity);

    const std::vector<Entity> &GetSystemEntities() const { return m_entities; }
    const Signature &GetComponentSignature() const { return m_component_signature; }

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

/////////////////////////////////////////////////////////////////////////////////
//--Pool
/////////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------//
// A pool is (a wrapper for) a vector of contiguous data of object of type T
//-----------------------------------------------------------------------------//
/////////////////////////////////////////////////////////////////////////////////
class IPool
{
public:
    virtual ~IPool() {}
};

template <typename T>
class Pool : public IPool
{
private:
    std::vector<T> data;

public:
    Pool(int size = 100) : data(size) {}
    virtual ~Pool() {}

    bool IsEmpty() const { return data.empty(); }
    int GetSize() const { return data.size(); }
    void Clear() { data.clear(); }
    void Resize(unsigned int size) { data.resize(size); }

    void Add(T object)
    {
        data.push_back(object);
    }

    const T &Get(unsigned int index) const { return this[index]; }
    T &Get(unsigned int index) { return this[index]; }
    void Set(unsigned int index, T object) { this[index] = object; }

    T &operator[](unsigned int index)
    {
        if (index >= size)
        {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    const T &operator[](unsigned int index) const
    {
        if (index >= size)
        {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }
};

/////////////////////////////////////////////////////////////////////////////////
//--Registry
/////////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------//
// The registry manages the entity creation & destruction, add systems,
// add components, etc.
//(other name: World, Entity Manager)
//-----------------------------------------------------------------------------//
/////////////////////////////////////////////////////////////////////////////////
class Registry
{
private:
    // keep track of all the entities in the scene
    std::size_t m_numberOfEntitnes = 0;

    // vector of component pools, each pool contains all the data for a certain component type
    //[vector index = component id]
    //[pool index = entity id]
    std::vector<IPool *> m_componentPools;

    // vector of component signatures per entity, saying which component is "on" for each entity
    //[vector index = entity id]
    std::vector<Signature> m_entityComponentSignatures;

    // keeping track of all systems
    std::unordered_map<std::type_index, System*> m_systems;

    // temporary sets to stored entites that are flagged to be added/removed in the next frame
    std::set<Entity> m_entitesToBeAdded;
    std::set<Entity> m_entitiesToBeRemoved;

public:
    Registry() = default;

    void Update();
    Entity CreateEntity();
    void AddEntityToSystem(const Entity& entity);
};

#endif