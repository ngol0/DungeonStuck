#include "InputEditorSystem.h"
#include "../../Input/InputManager.h"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl2.h>
#include <imgui/imgui_impl_sdlrenderer2.h>

auto &inputManager = InputManager::GetInstance();

InputEditorSystem::InputEditorSystem()
{
    keyMap = {
        {SDLK_a, "A"},
        {SDLK_b, "B"},
        {SDLK_c, "C"},
        {SDLK_d, "D"},
        {SDLK_e, "E"},
        {SDLK_f, "F"},
        {SDLK_g, "G"},
        {SDLK_h, "H"},
        {SDLK_i, "I"},
        {SDLK_j, "J"},
        {SDLK_k, "K"},
        {SDLK_l, "L"},
        {SDLK_m, "M"},
        {SDLK_n, "N"},
        {SDLK_o, "O"},
        {SDLK_p, "P"},
        {SDLK_q, "Q"},
        {SDLK_r, "R"},
        {SDLK_s, "S"},
        {SDLK_t, "T"},
        {SDLK_u, "U"},
        {SDLK_v, "V"},
        {SDLK_w, "W"},
        {SDLK_x, "X"},
        {SDLK_y, "Y"},
        {SDLK_z, "Z"},
        {SDLK_0, "0"},
        {SDLK_1, "1"},
        {SDLK_2, "2"},
        {SDLK_3, "3"},
        {SDLK_4, "4"},
        {SDLK_5, "5"},
        {SDLK_6, "6"},
        {SDLK_7, "7"},
        {SDLK_8, "8"},
        {SDLK_9, "9"},
        {SDLK_SPACE, "Space"},
        {SDLK_RETURN, "Enter"},
        {SDLK_ESCAPE, "Escape"},
        // {SDLK_LSHIFT, "Left Shift"},
        // {SDLK_RSHIFT, "Right Shift"},
        // {SDLK_LCTRL, "Left Ctrl"},
        // {SDLK_RCTRL, "Right Ctrl"},
        // {SDLK_LALT, "Left Alt"},
        // {SDLK_RALT, "Right Alt"},
        // {SDLK_LEFT, "Left Arrow"},
        // {SDLK_RIGHT, "Right Arrow"},
        // {SDLK_UP, "Up Arrow"},
        // {SDLK_DOWN, "Down Arrow"},
        // Add more keys as needed
    };
}

void InputEditorSystem::Init()
{
    for (const auto &pair : keyMap)
    {
        keyCodes.push_back(pair.first);
        keyNames.push_back(pair.second.c_str());
    }

    for (const auto &pair : inputManager.m_ActionNameKeyMap)
    {
        actionNames.push_back(pair.first);

        for (unsigned int i = 0; i < keyCodes.size(); ++i)
        {
            if (pair.second == keyCodes[i])
            {
                items.push_back(static_cast<int>(i));
                break;
            }
        }
        continue;
    }

    spdlog::info(items.size());
}

void InputEditorSystem::Render(SDL_Renderer *renderer)
{
    if (!isDebugging)
        return;

    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    // editor here
    //ImGui::ShowDemoWindow();
    //-------------
    ImGui::Begin("Input Editor");
    ImGui::Text("Use this to rebind input and action");

    for (unsigned int i = 0; i < actionNames.size(); ++i)
    {
        if (ImGui::CollapsingHeader(actionNames[i].c_str(), ImGuiTreeNodeFlags_DefaultOpen))
        {
            std::string comboLabel = "Key##" + actionNames[i];
            std::string buttonLabel = "Save##" + actionNames[i];
            ImGui::Combo(comboLabel.c_str(), &items[i], keyNames.data(), static_cast<int>(keyNames.size()));

            ImGui::BeginDisabled(inputManager.IsKeyExist(keyCodes[items[i]]));
            if (ImGui::Button(buttonLabel.c_str()))
            {
                RebindKey(actionNames[i], keyCodes[items[i]]);
            }
            ImGui::EndDisabled();
        }
    }

    ImGui::End();

    //-------------

    ImGui::Render();
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer);
}

void InputEditorSystem::RebindKey(const std::string &actionName, SDL_Keycode key)
{
    inputManager.RebindKey(actionName, key);
    spdlog::info("Successfully rebinding action " + actionName);
}
