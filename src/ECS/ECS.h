#ifndef ECS_H
#define ECS_H

class Component
{
};

class Entity
{
private:
    int id;

public:
    Entity(const int &id);
    int GetId() const { return id; }
};

/////////////////////////////////////////////////////////////////
//-------------------------------------------------------------//
//The system processes entities that contain a specific signature
//-------------------------------------------------------------//
/////////////////////////////////////////////////////////////////
class System
{
private:

public:
};

class Registry
{
};

#endif