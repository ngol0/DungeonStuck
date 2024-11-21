#include "Utils.h"

namespace Utils
{
    glm::vec2 GridToWordPos(GridPosition gridPos)
    {
        float x = gridPos.x * 32.f + 16.f;
        float y = gridPos.y * 32.f + 16.f;

        return glm::vec2{x,y};
    }

    GridPosition TileToGridPos(glm::vec2 tilePos)
    {
        int x = tilePos.x/32.f;
        int y = tilePos.y/32.f;

        return GridPosition{x, y};
    }
}