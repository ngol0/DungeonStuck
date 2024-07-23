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

    bool operator<(const Entity &other) const
    {
        return m_id < other.m_id;
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
    void Set(unsigned int index, T& object) { this[index] = object; }

    T &operator[](unsigned int index)
    {
        if (index >= data.size())
        {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    const T &operator[](unsigned int index) const
    {
        if (index >= data.size())
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
    std::unordered_map<std::type_index, System *> m_systems;

    // temporary sets to stored entites that are flagged to be added/removed in the next frame
    std::set<Entity> m_entitesToBeAdded;
    std::set<Entity> m_entitiesToBeRemoved;

public:
    Registry() = default;
    ~Registry();

    void Update();

    //Entity Managements
    Entity CreateEntity();
    void AddEntityToSystem(const Entity& entity);

    //Component Management
    template <typename TComponent, typename... TArgs> void AddComponent(const Entity &e, TArgs &&...args);
    template <typename TComponent> void RemoveComponent(const Entity &e);
    template <typename TComponent> bool HasComponent(const Entity &e) const;
    template <typename TComponent> TComponent& GetComponent(const Entity &e);

    //System Management
    template <typename TSystem, typename... TArgs> void AddSystem(TArgs &&...args);
    template <typename TSystem> void RemoveSystem();
    template <typename TSystem> bool HasSystem() const;
    template <typename TSystem> TSystem& GetSystem();
};

//---Component Management implementation
template <typename TComponent, typename... TArgs>
void Registry::AddComponent(const Entity &e, TArgs &&...args)
{
    // get component && entity id
    const auto componentId = Component<TComponent>::GetId();
    const auto entityId = e.GetId();

    // allocate memory for the new pool
    if (componentId >= m_componentPools.size())
    {
        m_componentPools.resize(componentId + 1, nullptr);
    }
    // create a new component pool (vector) of type TComponent (i.e: Transform/BoxCollider/etc.)
    // put it in the vector of component pools
    if (m_componentPools[componentId] == nullptr)
    {
        m_componentPools[componentId] = new Pool<TComponent>();
    }

    // create concrete component and assign it to the entity
    // and turn the component signature on for that entity
    TComponent newComponent(std::forward<TArgs>(args)...);
    m_componentPools[componentId]->Set(entityId, newComponent); // set the component to the entity at index id
    m_entityComponentSignatures[entityId].set(componentId);
}

template <typename TComponent>
void Registry::RemoveComponent(const Entity &e)
{
    const auto componentId = Component<TComponent>::GetId();
    const auto entityId = e.GetId();

    m_entityComponentSignatures[entityId].reset(componentId);
}

template <typename TComponent>
bool Registry::HasComponent(const Entity &e) const
{
    const auto componentId = Component<TComponent>::GetId();
    return m_entityComponentSignatures[e.GetId()].test(componentId);
}

template <typename TComponent>
TComponent& Registry::GetComponent(const Entity &e)
{
    const auto componentId = Component<TComponent>::GetId();
    const auto entityId = e.GetId();

    if (!m_entityComponentSignatures[entityId].test(componentId))
        return nullptr;

    return m_componentPools[componentId].Get(entityId);
}

//---System Management implementation

//todo: look up type_index(typeid) & why use unordered_map.find(type_index)
template <typename TSystem, typename... TArgs> 
void Registry::AddSystem(TArgs &&...args)
{
    //create a new system
    TSystem* newSystem = new TSystem(std::forward<TArgs>(args)...);

    //make_pair move the val instead of copying it
    m_systems.insert(std::make_pair(std::type_index(typeid(TSystem)), newSystem));
}

template <typename TSystem> 
void Registry::RemoveSystem()
{
    //erase by key
    m_systems.erase(std::type_index(typeid(TSystem)));
}

template <typename TSystem> 
bool Registry::HasSystem() const
{
    return m_systems.find(std::type_index(typeid(TSystem))) != m_systems.end();
}

template <typename TSystem>
TSystem& Registry::GetSystem()
{
    auto iter = m_systems.find(std::type_index(typeid(TSystem)));

    //iter->second returns a pointer to a System
    //cast System to a specific system and dereference it
    return *(std::static_pointer_cast<TSystem>(iter->second));
}


#endif