#ifndef PATHFINDINGEDITOR_H
#define PATHFINDINGEDITOR_H

#include "../../ECS/ECS.h"

class PathfindingDebugEditor : public System
{
public:
    PathfindingDebugEditor() {}

    void Render(SDL_Renderer *renderer) override;
};

#endif