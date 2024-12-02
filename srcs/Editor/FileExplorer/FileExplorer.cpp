#include "Editor/FileExplorer/FileExplorer.hpp"
#include "imgui.h"

FileExplorer::FileExplorer()
{
}

FileExplorer::~FileExplorer()
{
}

void FileExplorer::Draw()
{
    ImGui::Begin("File Explorer");

    isHoveredOrFocused = ImGui::IsWindowHovered() || ImGui::IsWindowFocused();

    ImGui::End();
}

bool FileExplorer::IsHoveredOrFocused() const
{
    return (isHoveredOrFocused);
}