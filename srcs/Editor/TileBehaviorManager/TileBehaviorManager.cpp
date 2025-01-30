#include "Editor/TileBehaviorManager/TileBehaviorManager.hpp"
#include "Common/TileBehaviorType.hpp"
#include "imgui.h"
#include <magic_enum.hpp>
#include <iostream>
TileBehaviorManager::TileBehaviorManager()
{
}

TileBehaviorManager::~TileBehaviorManager()
{
}

void TileBehaviorManager::Draw()
{
    ImGui::Begin("Tile Behavior Manager");

    isHoveredOrFocused = ImGui::IsWindowHovered() || ImGui::IsWindowFocused();

    auto values = magic_enum::enum_values<TileBehaviorType>();
    for (auto it = values.begin(); it != values.end(); it++)
    {
        std::string name = std::string(magic_enum::enum_name(*it).data());
        ImGui::Text("%s", name.c_str());
    }

    ImGui::End();
}