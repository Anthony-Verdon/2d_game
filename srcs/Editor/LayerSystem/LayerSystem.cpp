#include "Editor/LayerSystem/LayerSystem.hpp"
#include "imgui.h"

LayerSystem::LayerSystem()
{
    layer = 0;
}

LayerSystem::~LayerSystem()
{

}

void LayerSystem::Draw()
{
    ImGui::Begin("Layer System");

    isHoveredOrFocused = ImGui::IsWindowHovered() || ImGui::IsWindowFocused();

    ImGui::InputInt("layer", &layer);

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