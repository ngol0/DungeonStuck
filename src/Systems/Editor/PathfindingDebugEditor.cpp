#include "PathfindingDebugEditor.h"
#include "../../Game/Scene.h"
#include "../../Game/AStarPathfinding.h"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl2.h>
#include <imgui/imgui_impl_sdlrenderer2.h>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>


void PathfindingDebugEditor::Render(SDL_Renderer *renderer)
{
    if (!Scene::isDebugging) return;

    ImGui::Begin("Pathfinding Debug");
    static int startPosX = 0;
    static int startPosY = 0;
    static int endPosX = 0;
    static int endPosY = 0;

    ImGui::SeparatorText("Start Position");
    if (ImGui::CollapsingHeader("Start Position", ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::InputInt("XS", &startPosX);
        ImGui::InputInt("YS", &startPosY);
    }

    ImGui::SeparatorText("End Position");
    if (ImGui::CollapsingHeader("End Position", ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::InputInt("XE", &endPosX);
        ImGui::InputInt("YE", &endPosY);
    }
    if (ImGui::Button("Create Path"))
    {
        GridPosition startPos(startPosX, startPosY);
        GridPosition endPos(endPosX, endPosY);

        std::vector<GridPosition> path = AStarPathfinding::GetInstance().FindPath(startPos, endPos);
        if (path.empty()) spdlog::info("Can't find path!");

        for (auto& step : path)
        {
            spdlog::info("(" + std::to_string(step.x) + ", " + std::to_string(step.y) + ") -> ");
            auto& node = AStarPathfinding::GetInstance().GetEntityAtGridPos(step).GetComponent<PathNodeComponent>();
            node.r = 0;
        }
    }
    if (ImGui::Button("Change Color"))
    {
        GridPosition startPos(startPosX, startPosY);
        GridPosition endPos(endPosX, endPosY);

        auto& start = AStarPathfinding::GetInstance().GetEntityAtGridPos(startPos).GetComponent<PathNodeComponent>();
        auto& end = AStarPathfinding::GetInstance().GetEntityAtGridPos(endPos).GetComponent<PathNodeComponent>();
        start.r = 0;
        end.g = 0;
    }
    ImGui::End();
}
