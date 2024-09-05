#include "EnemySpawnEditor.h"
#include "../../Components/TransformComponent.h"
#include "../../Components/SpriteComponent.h"
#include "../../Components/BoxColliderComponent.h"
#include "../../Components/HealthComponent.h"
#include "../../Game/EntityFactory.h"
#include "../../Global/GlobalDataType.h"
#include "../../Game/Scene.h"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl2.h>
#include <imgui/imgui_impl_sdlrenderer2.h>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>


void EnemySpawnEditor::Render(SDL_Renderer *renderer)
{
    if (!Scene::isDebugging) return;

    ImGui::Begin("Spawn Enemies");
    static int enemyXPos = 0;
    static int enemyYPos = 0;
    static float enemyDirectionX = 1.0f;
    static float enemyDirectionY = 0.0f;

    ImGui::SeparatorText("Enemy Position");
    if (ImGui::CollapsingHeader("Enemy Position", ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::InputInt("X Position", &enemyXPos);
        ImGui::InputInt("Y Position", &enemyYPos);
    }

    ImGui::SeparatorText("Enemy Speed");
    if (ImGui::CollapsingHeader("Enemy Direction", ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::InputFloat("Direction X", &enemyDirectionX);
        ImGui::InputFloat("Direction Y", &enemyDirectionY);
    }
    if (ImGui::Button("Spawn Enemy"))
    {
        EntityFactory::CreateEnemy(glm::vec2(enemyXPos, enemyYPos), glm::vec2(enemyDirectionX, enemyDirectionY), EnemyType::SLIME);
    }
    ImGui::End();
}
