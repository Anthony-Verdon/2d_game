#include "Editor/LayerSystem/LayerSystem.hpp"
#include "imgui.h"

LayerSystem::LayerSystem()
{
    layer = 0;
}

LayerSystem::~LayerSystem()
{

}

void LayerSystem::Draw(const Tilemap &tilemap)
{
    ImGui::Begin("Layer System");

    isHoveredOrFocused = ImGui::IsWindowHovered() || ImGui::IsWindowFocused();

    ImGui::InputInt("layer", &layer);

    std::set<int> layerLevels;
    const std::set<Tile>& tiles = tilemap.GetTiles();
    for (auto it = tiles.begin(); it != tiles.end(); it++)
    {
        layerLevels.insert(it->layer);
    }

    for (auto it = layerLevels.begin(); it != layerLevels.end(); it++)
    {
        std::string button = "layer " + std::to_string(*it);
        if (ImGui::Button(button.c_str()))
        {
            layer = *it;
        }
    }

    ImGui::End();
}

int LayerSystem::GetLayer() const
{
    return (layer);
}

bool LayerSystem::IsHoveredOrFocused() const
{
    return (isHoveredOrFocused);
}