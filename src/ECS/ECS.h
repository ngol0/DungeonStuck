#ifndef ECS_H
#define ECS_H

#include <bitset>
#include <vector>
#include <unordered_map>
#include <typeindex>
#include <set>
#include <spdlog/spdlog.h>

struct SDL_Renderer;

inline std::size_t GetUniqueId()
{
    static std::size_t lastId{0u};
    return lastId++; // return the value first, then increment
}

template <typename T>
struct Component
{
    static std::size_t GetId()
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
    class Registry* m_registry;

public:
    Entity(int id, Registry& registry);
    
    int GetId() const { return m_id; }

    template <typename TComponent, typename... TArgs> void AddComponent(TArgs &&...args);
    template <typename TComponent> void RemoveComponent();
    template <typename TComponent> bool HasComponent() const;
    template <typename TComponent> TComponent* GetComponent();
    //template <typename TComponent> const TComponent& GetComponent() const;

    //operator overload
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
using Signature = std::bitset<MAX_COMPONENTS>;

class System
{
private:
    // which components an entity must have for the system to consider the entity
    Signature m_component_signature;

    // list of all entities that a system is interested in
    std::vector<Entity> m_entities;

public:
    System() = default;
    virtual ~System() = default;

    virtual void Update(float dt) {}
    virtual void Render(SDL_Renderer* renderer) {}

    void AddEntityToSystem(const Entity &entity);
    void RemoveEntityFromSystem(const Entity &entity);

    std::vector<Entity> &GetSystemEntities() { return m_entities; }
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
    Pool(int size = 100) 
    {
        //if use resize > data will init the members and call its default constructor of TComponent
        data.resize(size);

        //todo: what does reserve do??
        //data.reserve(size); //this will not init the members and doesnot need default constructor for TComponent
    }
    virtual ~Pool() {}

    bool IsEmpty() const { return data.empty(); }
    int GetSize() const { return data.size(); }
    void Clear() { data.clear(); }
    void Resize(unsigned int size) { data.resize(size); }

    void Add(T object)
    {
        data.push_back(object);
    }

    const T &Get(unsigned int index) const { return (*this)[index]; }
    T &Get(unsigned int index) { return (*this)[index]; }
    void Set(unsigned int index, T& object) { data[index] = object; }

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
    //----
    //uncomment this for smart pointer
    //std::vector<std::shared_ptr<IPool>> m_componentPools; 
    std::vector<IPool*> m_componentPools;

    // vector of component signatures per entity, saying which component is "on" for each entity
    //[vector index = entity id]
    std::vector<Signature> m_entityComponentSignatures;

    // keeping track of all systems
    std::unordered_map<std::type_index, System *> m_systems;

    // temporary sets to stored entites that are flagged to be added/removed in the next frame
    std::set<Entity> m_entitesToBeAdded;
    std::set<Entity> m_entitiesToBeRemoved;
    
    void AddEntityToSystem(const Entity& entity);

public:
    Registry() = default;
    ~Registry();

    void Update(float dt);
    void Render(SDL_Renderer* renderer);

    //Entity Managements
    Entity CreateEntity();

    //Component Management
    template <typename TComponent, typename... TArgs> void AddComponent(const Entity &e, TArgs &&...args);
    template <typename TComponent> void RemoveComponent(const Entity &e);
    template <typename TComponent> bool HasComponent(const Entity &e) const;
    template <typename TComponent> TComponent* GetComponent(const Entity &e);
    //template <typename TComponent> const TComponent& GetComponent(const Entity &e) const;

    //System Management
    template <typename TSystem, typename... TArgs> void AddSystem(TArgs &&...args);
    template <typename TSystem> void RemoveSystem();
    template <typename TSystem> bool HasSystem() const;
    template <typename TSystem> TSystem& GetSystem();
    template <typename TSystem> const TSystem& GetSystem() const;
};

//---Component Management implementation
//Registry
template <typename TComponent, typename... TArgs>
void Registry::AddComponent(const Entity &e, TArgs &&...args)
{
    // get component && entity id
    auto componentId = Component<TComponent>::GetId();
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
        //--if use smart pointer:
        //m_componentPools[componentId] = std::make_shared<Pool<TComponent>>();

        //--if use raw ptrs: 
        m_componentPools[componentId] = new Pool<TComponent>();
    }

    //--if use smart pointer:
    //m_componentPools[componentId] returns a shared_ptr<IPool>
    //thus, we cast it to Pool<TComponent> shared_ptr and store it in pool
    //std::shared_ptr<Pool<TComponent>> pool = std::static_pointer_cast<Pool<TComponent>>(m_componentPools[componentId]); //uncomment this for smart pointer

    //--if use raw ptrs:
    auto pool = static_cast<Pool<TComponent>*>(m_componentPools[componentId]);

    // create concrete component and assign it to the entity
    // and turn the component signature on for that entity
    TComponent newComponent(std::forward<TArgs>(args)...);
    
    pool->Set(entityId, newComponent); // set the component to the entity at index id
    m_entityComponentSignatures[entityId].set(componentId);

    spdlog::info("Component id " + std::to_string(componentId) + " was added to entity id " + std::to_string(entityId));
}

template <typename TComponent>
void Registry::RemoveComponent(const Entity &e)
{
    auto componentId = Component<TComponent>::GetId();
    const auto entityId = e.GetId();

    m_entityComponentSignatures[entityId].reset(componentId);
}

template <typename TComponent>
bool Registry::HasComponent(const Entity &e) const
{
    auto componentId = Component<TComponent>::GetId();
    return m_entityComponentSignatures[e.GetId()].test(componentId);
}

template <typename TComponent>
TComponent* Registry::GetComponent(const Entity &e)
{
    if (!HasComponent<TComponent>(e))
    {
        return nullptr;
    }

    auto componentId = Component<TComponent>::GetId();
    const auto entityId = e.GetId();

    return &static_cast<Pool<TComponent>*>(m_componentPools[componentId])->Get(entityId);    
    //return std::static_pointer_cast<Pool<TComponent>>(m_componentPools[componentId])->Get(entityId); //for smart pointer
}

//---System Management implementation

//todo: look up type_index(typeid) & why use unordered_map.find(type_index)
template <typename TSystem, typename... TArgs> 
void Registry::AddSystem(TArgs &&...args)
{
    //create a new system
    TSystem* newSystem = new TSystem(std::forward<TArgs>(args)...);

    //question: do we need to make sure TSystem is a derived class of System before adding??

    //make_pair move the val instead of copying it: https://cplusplus.com/reference/unordered_map/unordered_map/insert/
    //but newSystem pointer is copied instead?
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
    return *(static_cast<TSystem*>(iter->second));
}

template <typename TSystem>
const TSystem& Registry::GetSystem() const
{
    auto iter = m_systems.find(std::type_index(typeid(TSystem)));

    //iter->second returns a pointer to a System
    //cast System to a specific system and dereference it
    return *(std::static_pointer_cast<TSystem>(iter->second));
}

//---Component Management implementation
//Entity
template <typename TComponent, typename... TArgs>
void Entity::AddComponent(TArgs &&...args)
{
    m_registry->AddComponent<TComponent>(*this, std::forward<TArgs>(args)...);
}

template <typename TComponent>
void Entity::RemoveComponent()
{
    m_registry->RemoveComponent<TComponent>(*this);
}

template <typename TComponent>
bool Entity::HasComponent() const
{
    return m_registry->HasComponent<TComponent>(*this);
}

template <typename TComponent>
TComponent* Entity::GetComponent()
{
    return m_registry->GetComponent<TComponent>(*this);
}

#endif