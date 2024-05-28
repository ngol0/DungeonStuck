#include <iostream>
#include "Game/Game.h"

int main() {
    Game game;

    game.InitWindow();
    game.Run();
    game.Destroy();

    return 0;
}
