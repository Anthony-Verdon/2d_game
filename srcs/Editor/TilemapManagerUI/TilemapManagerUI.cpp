#include "Editor/TilemapManagerUI/TilemapManagerUI.hpp"
#include "imgui.h"

TilemapManagerUI::TilemapManagerUI(): AEditorWindow()
{
    tilemapSelected = "";
    name[0] = 0;
}

TilemapManagerUI::~TilemapManagerUI()
{

}

void TilemapManagerUI::Draw()
{
    ImGui::Begin("Tilemap Manager");

    isHoveredOrFocused = ImGui::IsWindowHovered() || ImGui::IsWindowFocused();

    ImGui::InputText("tilemap name", name, IM_ARRAYSIZE(name));
    if (ImGui::Button("new tilemap", ImVec2(100, 40)))
    {
        tilemapManager.AddTilemap(name);
        name[0] = 0;
    }

    std::vector<std::string> tilemapOrder = tilemapManager.GetTilemapOrder();
    for (size_t i = 0; i < tilemapOrder.size(); i++)
    {
        std::string item = tilemapOrder[i];
        if (ImGui::Selectable(item.c_str(), item == tilemapSelected))
            tilemapSelected = item;

        if (ImGui::IsItemActive() && !ImGui::IsItemHovered())
        {
            size_t i_next = i + (ImGui::GetMouseDragDelta(0).y < 0.f ? -1 : 1);
            if (i_next >= 0 && i_next < tilemapOrder.size())
            {
                std::swap(tilemapOrder[i], tilemapOrder[i_next]);
                ImGui::ResetMouseDragDelta();
            }
        }
    }
    tilemapManager.SetTilemapOrder(tilemapOrder);

    ImGui::End();

    tilemapManager.Draw();
}

void TilemapManagerUI::AddTile(const glm::vec2 &position, const Tile &tile)
{
    tilemapManager.AddTile(tilemapSelected, position, tile);
}

void TilemapManagerUI::AddTile(const glm::vec2 &position, const Sprite &sprite)
{
    tilemapManager.AddTile(tilemapSelected, position, sprite);
}

void TilemapManagerUI::SuppressTile(const glm::vec2 &position)
{
    tilemapManager.SuppressTile(tilemapSelected, position);

}