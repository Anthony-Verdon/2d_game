#include <iostream>
#include "Engine/WindowManager/WindowManager.hpp"
#include "globals.hpp"
#include "Editor/Editor.hpp"
#include <filesystem>

int main()
{
    // @todo: put ImGUI as a parameter in WindowManager to destroy it correctly
    // actually, it's destroye in ~Editor which cause errors for GLFW
    std::cout << "welcome in the editor" << std::endl;
    WindowManager::InitWindow("new editor");
    Editor editor;
    WindowManager::StartUpdateLoop(&editor);
    WindowManager::DestructWindowManager();
    std::cout << "end" << std::endl;
    return (EXIT_SUCCESS);
}