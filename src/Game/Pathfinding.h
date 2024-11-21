#ifndef PATHFINDING_H
#define PATHFINDING_H

#include "../ECS/ECS.h"
#include "../Global/Utils.h"
#include <unordered_set>

// Node structure
struct ListNode 
{
    int entityId;
    ListNode* next;

    ListNode(int val, ListNode* next = nullptr) : entityId(val), next(next) {}
};

class Pathfinding
{
public:
    Entity grid[40][30];

    Pathfinding();
    Pathfinding(const Pathfinding&) = delete;

    void Init();

    //singleton
    static Pathfinding& GetInstance();

    ListNode* FindPath(GridPosition startPos, GridPosition endPos);
    ListNode* MakePath(Entity curEntity);
    ListNode* ReverseList(ListNode* head);
    void ResetPathfindingData();

    std::unordered_set<int> GetNeighborList(Entity curEntity);

    int CalculateFCost(Entity e);
    int CalculateDistance(GridPosition currentPos, GridPosition endPos);

    Entity GetEntityWithLowestFCost(std::unordered_set<int> listNodes);

    bool IsValidGridPos(GridPosition gridPos);

    Entity GetEntityAtGridPos(GridPosition gridPos)
    {
        return grid[gridPos.x][gridPos.y];
    }

    void SetGridPos(Entity e, GridPosition gridPos)
    {
        grid[gridPos.x][gridPos.y] = e;
    }
};

#endif