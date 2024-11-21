#include "Pathfinding.h"

#include "../Components/PathNodeComponent.h"

Pathfinding::Pathfinding()
{

}

void Pathfinding::Init()
{
    
}

int Pathfinding::CalculateFCost(Entity e)
{
    auto& node = e.GetComponent<PathNodeComponent>();
    return node.gCost + node.hCost;
}

int Pathfinding::CalculateDistance(GridPosition currentPos, GridPosition endPos)
{
    int dx = std::abs(currentPos.x - endPos.x);
    int dy = std::abs(currentPos.y - endPos.y);

    return 10 * (dx + dy) + (14 - 2 * 10) * std::min(dx, dy);
}

ListNode* Pathfinding::FindPath(GridPosition startPos, GridPosition endPos)
{
    std::unordered_set<int> openList;
    std::unordered_set<int> closedList;

    Entity startEntity = GetEntityAtGridPos(startPos);
    Entity endEntity = GetEntityAtGridPos(endPos);

    openList.insert(startEntity.GetId());

    ResetPathfindingData(); //todo: implement this

    auto& startNode = startEntity.GetComponent<PathNodeComponent>();

    startNode.gCost = 0;
    startNode.hCost = CalculateDistance(startPos, endPos);
    CalculateFCost(startEntity);

    while (openList.size() > 0)
    {
        Entity curEntity = GetEntityWithLowestFCost(openList);
        auto& curPathNode = curEntity.GetComponent<PathNodeComponent>();

        if (closedList.count(curEntity.GetId()) > 0) //if already searched
        {
            continue;
        }

        if (curEntity == endEntity)
        {
            //Debug.Log("reached here???");
            return MakePath(curEntity);
        }

        openList.erase(curEntity.GetId());
        closedList.insert(curEntity.GetId());

        //look at all neighbors
        for (const auto& neighborId : GetNeighborList(curEntity))
        {
            Entity neighborEntity = Entity(neighborId);
            auto& neighborNode = neighborEntity.GetComponent<PathNodeComponent>();
            if (closedList.count(neighborId)) continue;
            if (!neighborNode.isWalkable)
            {
                closedList.insert(neighborId);
                continue;
            }

            int currentGCost = curPathNode.gCost + CalculateDistance(curPathNode.gridPos, neighborNode.gridPos);

            if (currentGCost < neighborNode.gCost)
            {
                // reset g h and f cost
                neighborNode.gCost = currentGCost;
                neighborNode.hCost = CalculateDistance(neighborNode.gridPos, endPos);
                CalculateFCost(neighborEntity);
                neighborNode.camefromEntityId = curEntity.GetId();

                if (!openList.count(neighborId))
                {
                    openList.insert(neighborId);
                }
            }
        }
    }

    return nullptr;
}


ListNode* Pathfinding::MakePath(Entity endEntity)
{
    ListNode* head = new ListNode(endEntity.GetId());

    while (endEntity.GetComponent<PathNodeComponent>().camefromEntityId != -1)
    {
        auto& pathNode = endEntity.GetComponent<PathNodeComponent>();
        head->next = new ListNode(pathNode.camefromEntityId);
        head = head->next;
        endEntity = Entity(pathNode.camefromEntityId);
    }

    return ReverseList(head);
}

ListNode* Pathfinding::ReverseList(ListNode* head)
{
    ListNode* previous = nullptr;
    ListNode* cur = head;

    while (cur!=nullptr)
    {
        cur = head->next;
        head->next = previous;
        previous = head;
        head = cur;
    }

    return head;
}

void Pathfinding::ResetPathfindingData()
{

}

Entity Pathfinding::GetEntityWithLowestFCost(std::unordered_set<int> listEntities)
{
    // // Check if the set is empty to avoid dereferencing an invalid iterator.
    if (listEntities.empty()) 
    {
        throw std::runtime_error("The set of nodes is empty.");
    }

    // Initialize `lowestNode` to the first element in the set
    auto it = listEntities.begin();
    Entity lowestEntity = *it;

    // Iterate through the rest of the set to find the lowest F cost
    for (++it; it != listEntities.end(); ++it) 
    {
        if (CalculateFCost(*it) < CalculateFCost(lowestEntity)) 
        {
            lowestEntity = *it;
        }
    }

    return lowestEntity;
}

std::unordered_set<int> Pathfinding::GetNeighborList(Entity curEntity)
{
    std::unordered_set<int> neighbourList;

    GridPosition gridPosition = curEntity.GetComponent<PathNodeComponent>().gridPos;

    for (int x = -1; x <= 1; x++)
    {
        for (int y = -1; y <= 1; y++)
        {
            if (x == 0 && y == 0)
                continue;

            int newX = gridPosition.x + x;
            int newY = gridPosition.y + y;
            GridPosition potentialNeighborPos = GridPosition{newX, newY};

            if (IsValidGridPos(potentialNeighborPos))
            {
                neighbourList.insert(GetEntityAtGridPos(potentialNeighborPos).GetId());
            }
        }
    }

    return neighbourList;
}

bool Pathfinding::IsValidGridPos(GridPosition gridPos)
{
    return 0 <= gridPos.x 
            && gridPos.x <= 39     
            && 0 <= gridPos.y 
            && gridPos.y <= 29;
}

//singleton
Pathfinding& Pathfinding::GetInstance()
{
    static Pathfinding manager;
	return manager;
}