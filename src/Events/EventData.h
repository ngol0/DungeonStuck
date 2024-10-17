#ifndef EVENTDATA_H
#define EVENTDATA_H

#include <utility>
#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>
#include "../Global/Interface.h"
#include "../Global/GlobalDataType.h"

struct CollisionEventData : public IData
{
    std::pair<int, int> collisionPair;
    SDL_Rect overlap;
    float dt;

    virtual ~CollisionEventData() = default;
    CollisionEventData(std::pair<int,int> pair, SDL_Rect rect, float d) : collisionPair(pair), overlap(rect), dt(d) {}
};


// struct AttackEventData : public IData
// {
//     WeaponType weaponType;

//     virtual ~AttackEventData() = default;
//     AttackEventData(WeaponType type) : weaponType(type) {}
// };

struct ItemEventData : public IData
{
    ItemType itemType;
    int amount;

    virtual ~ItemEventData() = default;
    ItemEventData(ItemType type = ItemType::NONE, int amount = 0) : itemType(type), amount(amount) {}
};

struct InventoryItemEventData : public IData
{
    ItemType itemType;
    int amount;
    int slot;

    virtual ~InventoryItemEventData() = default;
    InventoryItemEventData(ItemType type = ItemType::NONE, int amount = 0, int slot = 0) 
        : itemType(type), amount(amount), slot(slot) {}
};

class KeyPressedEventData : public IData
{
public:
    SDL_Keycode key;
    KeyPressedEventData(SDL_Keycode key) : key(key) {}
};

#endif