#include <iostream>
#include "Engine/WindowManager/WindowManager.hpp"
#include "Engine/Renderers/SpriteRenderer/SpriteRenderer.hpp"
#include "globals.hpp"
#include "Editor/Editor.hpp"

int main()
{
    std::cout << "welcome in the editor" << std::endl;
    WindowManager::InitWindow("new editor", WINDOW_WIDTH, WINDOW_HEIGHT);
    Editor editor;
    WindowManager::StartUpdateLoop(&editor);
    WindowManager::DestructWindowManager();
    std::cout << "end" << std::endl;
    return (EXIT_SUCCESS);
}