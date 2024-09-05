#ifndef INPUTEDITOR_H
#define INPUTEDITOR_H

#include "../../ECS/ECS.h"
#include <SDL2/SDL.h>

class InputEditorSystem : public System
{
private:
    //bool isDebugging{true};

    std::map<SDL_Keycode, std::string> keyMap;

    std::vector<SDL_Keycode> keyCodes;
    std::vector<const char*> keyNames;

    std::vector<int> items;
    std::vector<std::string> actionNames;

public:
    InputEditorSystem();

    void Init() override;
    void Render(SDL_Renderer *renderer) override;
    void RebindKey(const std::string& actionName, SDL_Keycode code);
};

#endif