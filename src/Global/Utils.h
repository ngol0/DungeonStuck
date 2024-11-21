#ifndef UTILITY_H
#define UTILITY_H

#include <glm/glm.hpp>
#include <functional> 

struct GridPosition
{
    int x;
    int y;

    GridPosition(int x = 0, int y = 0) : x(x), y(y) {}

    bool operator==(const GridPosition& other) const 
    {
        return x == other.x && y == other.y;
    }

    bool operator!=(const GridPosition& other) const 
    {
        return x != other.x || y != other.y;
    }
};


struct GridPositionHash 
{
    std::size_t operator()(const GridPosition& pos) const 
    {
        // Combine hashes of x and y (basic hash combination)
        return std::hash<int>()(pos.x) ^ (std::hash<int>()(pos.y) << 1);
    }
};

namespace Utils
{
    glm::vec2 GridToWordPos(GridPosition gridPos);
    GridPosition TileToGridPos(glm::vec2 tilePos);

    // GridPos WorldToGridPos(glm::vec2 worldPos)
    // {

    // }
};

#endif