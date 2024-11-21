#include "AStarPathfinding.h"

#include <queue>
#include <cmath>
#include <algorithm>
#include <limits>

AStarPathfinding::AStarPathfinding()
{

}

void AStarPathfinding::Init()
{
    
}

int AStarPathfinding::CalculateDistance(GridPosition currentPos, GridPosition endPos)
{
    int dx = std::abs(currentPos.x - endPos.x);
    int dy = std::abs(currentPos.y - endPos.y);

    return 10 * (dx + dy) + (14 - 2 * 10) * std::min(dx, dy);
}

std::vector<GridPosition> AStarPathfinding::FindPath(GridPosition startPos, GridPosition endPos)
{
    std::priority_queue<PathNodeComponent*, std::vector<PathNodeComponent*>, ComparePathNode> openSet;
    std::unordered_set<GridPosition, GridPositionHash> closedSet;
    std::unordered_set<PathNodeComponent*> openSetTracker; // To track membership

    Entity startEntity = GetEntityAtGridPos(startPos);
    PathNodeComponent* startNode = startEntity.GetComponentPtr<PathNodeComponent>();

    openSet.emplace(startNode);
    openSetTracker.insert(startNode);

    // reset all nodes data
    ResetPathfindingData();

    // set start node data
    startNode->gCost = 0;
    startNode->hCost = CalculateDistance(startPos, endPos);
    startNode->fCost = startNode->gCost + startNode->hCost;

    // Lambda to reconstruct path from goal to start
    auto reconstructPath = [](PathNodeComponent* node) 
    {
        std::vector<GridPosition> path;
        while (node) 
        {
            path.push_back(node->gridPos);
            node = node->parentNode;
        }
        std::reverse(path.begin(), path.end());
        return path;
    };

    while (!openSet.empty()) 
    {
        PathNodeComponent* current = openSet.top();
        openSet.pop();
        openSetTracker.erase(current);
        
        if (current->gridPos == endPos) 
        {
            return reconstructPath(current);
        }

        closedSet.insert(current->gridPos);

        for (const auto& neighborPos : GetNeighborList(current->gridPos))
        {
            if (!IsValidGridPos(neighborPos) || closedSet.count(neighborPos) > 0) continue;
            
            int currentGCost = current->gCost + CalculateDistance(current->gridPos, neighborPos);

            PathNodeComponent* neighborNode = GetEntityAtGridPos(neighborPos).GetComponentPtr<PathNodeComponent>();

            if (currentGCost < neighborNode->gCost)
            {
                neighborNode->gCost = currentGCost;
                neighborNode->hCost = CalculateDistance(neighborNode->gridPos, endPos);
                neighborNode->fCost = neighborNode->gCost + neighborNode->hCost;
                neighborNode->parentNode = current;

                if (openSetTracker.find(neighborNode) == openSetTracker.end())
                {
                    openSet.emplace(neighborNode);
                    openSetTracker.insert(neighborNode);
                }
            }
        }
    }
    return {}; 
}


std::unordered_set<GridPosition, GridPositionHash> AStarPathfinding::GetNeighborList(GridPosition curPos)
{
    std::unordered_set<GridPosition, GridPositionHash> neighbourList;

    for (int x = -1; x <= 1; x++)
    {
        for (int y = -1; y <= 1; y++)
        {
            if (x == 0 && y == 0)
                continue;

            int newX = curPos.x + x;
            int newY = curPos.y + y;
            GridPosition potentialNeighborPos = GridPosition{newX, newY};

            if (IsValidGridPos(potentialNeighborPos))
            {
                neighbourList.insert(potentialNeighborPos);
            }
        }
    }

    return neighbourList;
}

bool AStarPathfinding::IsValidGridPos(GridPosition gridPos)
{
    return 0 <= gridPos.x 
            && gridPos.x <= GRID_WIDTH - 1    
            && 0 <= gridPos.y 
            && gridPos.y <= GRID_HEIGHT - 1;
}

void AStarPathfinding::ResetPathfindingData()
{
    for (int x = 0; x < GRID_WIDTH; x++)
    {
        for (int z = 0; z < GRID_HEIGHT; z++)
        {
            GridPosition gridPos(x, z);
            auto& node = GetEntityAtGridPos(gridPos).GetComponent<PathNodeComponent>();
            node.parentNode = nullptr;
            node.gCost = std::numeric_limits<int>::max();
            node.hCost = 0;
            node.fCost = node.hCost + node.gCost;
            node.r = 255;
            node.g = 255;
            node.b = 0;
        }
    }
}

//singleton
AStarPathfinding& AStarPathfinding::GetInstance()
{
    static AStarPathfinding manager;
	return manager;
}