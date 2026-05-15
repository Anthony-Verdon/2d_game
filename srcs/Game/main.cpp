#include <iostream>
#include "Engine/WindowManager/WindowManager.hpp"
#include "globals.hpp"
#include "Game/Game.hpp"

int main()
{
    std::cout << "welcome in the new game" << std::endl;
    WindowManager::InitWindow("new game");
    WindowManager::SetClearColor(0.5, 0.5, 0.5, 0.5);
    WindowManager::EnableBlend(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    Game game;
    WindowManager::StartUpdateLoop(&game);
    WindowManager::DestructWindowManager();
    std::cout << "end" << std::endl;
    return (EXIT_SUCCESS);
}