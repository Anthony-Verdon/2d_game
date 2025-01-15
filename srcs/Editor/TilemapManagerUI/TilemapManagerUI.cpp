#include "Editor/TilemapManagerUI/TilemapManagerUI.hpp"
#include "imgui.h"

TilemapManagerUI::TilemapManagerUI(): AEditorWindow()
{
}

TilemapManagerUI::~TilemapManagerUI()
{

}

void TilemapManagerUI::Draw()
{
    ImGui::Begin("Tilemap Manager");

    isHoveredOrFocused = ImGui::IsWindowHovered() || ImGui::IsWindowFocused();

    ImGui::End();
}