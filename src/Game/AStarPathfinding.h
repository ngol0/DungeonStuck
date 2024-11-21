#ifndef ASTARPATHFINDING_H
#define ASTARPATHFINDING_H

#include "../ECS/ECS.h"
#include "../Global/Utils.h"
#include "../Components/PathNodeComponent.h"

#include <unordered_set>

struct ComparePathNode {
    bool operator()(const PathNodeComponent* lhs, const PathNodeComponent* rhs) const 
    {
        return *lhs > *rhs; // Assuming PathNodeComponent overloads operator>
    }
};

class AStarPathfinding
{
public:
    const static int GRID_WIDTH = 40;
    const static int GRID_HEIGHT = 30;
    Entity grid[GRID_WIDTH][GRID_HEIGHT];

    AStarPathfinding();
    AStarPathfinding(const AStarPathfinding&) = delete;

    void Init();

    //singleton
    static AStarPathfinding& GetInstance();

    std::vector<GridPosition> FindPath(GridPosition startPos, GridPosition endPos);
    std::unordered_set<GridPosition, GridPositionHash> GetNeighborList(GridPosition curPos);

    int CalculateDistance(GridPosition currentPos, GridPosition endPos);
    bool IsValidGridPos(GridPosition gridPos);

    Entity GetEntityAtGridPos(GridPosition gridPos)
    {
        return grid[gridPos.x][gridPos.y];
    }

    void SetGridPos(Entity e, GridPosition gridPos)
    {
        grid[gridPos.x][gridPos.y] = e;
    }

    void ResetPathfindingData();
};

#endif