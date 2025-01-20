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
        TilemapManager::AddTilemap(name);
        name[0] = 0;
    }

    std::vector<std::string> tilemapOrder = TilemapManager::GetTilemapOrder();
    for (size_t i = 0; i < tilemapOrder.size();)
    {
        std::string item = tilemapOrder[i];

        bool closable_group = true;
        ImGui::SetNextItemOpen(tilemapSelected == item);
        if (ImGui::CollapsingHeader(item.c_str(), &closable_group))
        {
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

            bool tilemapBuildCollision = TilemapManager::GetBuildCollision(tilemapSelected);
            std::string checkboxName = "Build collision ###" + std::to_string(i);
            ImGui::Checkbox(checkboxName.c_str(), &tilemapBuildCollision);
            TilemapManager::SetBuildCollision(tilemapSelected, tilemapBuildCollision);
        }
        else
        {
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

        if (closable_group)
            i++;
        else
            tilemapOrder.erase(tilemapOrder.begin() + i);
    }
    TilemapManager::SetTilemapOrder(tilemapOrder);

    ImGui::End();

    TilemapManager::Draw();
}

void TilemapManagerUI::AddTile(const glm::vec2 &position, const Tile &tile)
{
    TilemapManager::AddTile(tilemapSelected, position, tile);
}

void TilemapManagerUI::AddTile(const glm::vec2 &position, const Sprite &sprite, const glm::vec2 &spriteOffset)
{
    TilemapManager::AddTile(tilemapSelected, position, sprite, spriteOffset);
}

void TilemapManagerUI::SuppressTile(const glm::vec2 &position)
{
    TilemapManager::SuppressTile(tilemapSelected, position);

}

void TilemapManagerUI::Load()
{
    TilemapManager::Load();
}

void TilemapManagerUI::Save()
{
    TilemapManager::Save();
}