#include <iostream>
#include "Engine/WindowManager/WindowManager.hpp"
#include "globals.hpp"
#include "Editor/Editor.hpp"
#include <filesystem>

int main()
{
    // @todo: put ImGUI as a parameter in WindowManager to destroy it correctly
    // actually, it's destroyed in ~Editor which cause errors for GLFW
    std::cout << "welcome in the editor" << std::endl;
    WindowManager::InitWindow("new editor");
    WindowManager::SetClearColor(0.5, 0.5, 0.5, 0.5);
    WindowManager::EnableBlend(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    Editor editor;
    WindowManager::StartUpdateLoop(&editor);
    WindowManager::DestructWindowManager();
    std::cout << "end" << std::endl;
    return (EXIT_SUCCESS);
}