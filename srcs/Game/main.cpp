#include <iostream>
#include "Engine/WindowManager/WindowManager.hpp"
#include "globals.hpp"
#include "Game/Game.hpp"

int main()
{
    std::cout << "welcome in the new game" << std::endl;
    WindowManager::InitWindow("new game", WINDOW_WIDTH, WINDOW_HEIGHT);
    Game game;
    WindowManager::StartUpdateLoop(&game);
    WindowManager::DestructWindowManager();
    std::cout << "end" << std::endl;
    return (EXIT_SUCCESS);
}