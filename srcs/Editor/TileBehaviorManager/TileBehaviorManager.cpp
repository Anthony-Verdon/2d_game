#include "Editor/TileBehaviorManager/TileBehaviorManager.hpp"
#include "imgui.h"
#include <magic_enum.hpp>
#include <iostream>
#include "Engine/TileDictionnary/TileDictionnary.hpp" // tmp
#include "Engine/RessourceManager/RessourceManager.hpp"
#include "globals.hpp"

TileBehaviorManager::TileBehaviorManager()
{
    auto values = magic_enum::enum_values<TileBehaviorType>();
    for (auto it = values.begin(); it != values.end(); it++)
        tilesBehavior[*it] = {};
}

TileBehaviorManager::~TileBehaviorManager()
{
}

void TileBehaviorManager::Init() //tmp
{
    size_t nbTile = TileDictionnary::GetDictionnarySize();
    auto it = tilesBehavior.begin();
    for (size_t i = 0; i < nbTile; i++)
        it->second.push_back(TileDictionnary::GetTile(i));
}

void TileBehaviorManager::Draw()
{
    ImGui::Begin("Tile Behavior Manager");

    isHoveredOrFocused = ImGui::IsWindowHovered() || ImGui::IsWindowFocused();

    for (auto itTileBehavior = tilesBehavior.begin(); itTileBehavior != tilesBehavior.end(); itTileBehavior++)
    {
        std::string name = std::string(magic_enum::enum_name(itTileBehavior->first).data());
        if (ImGui::CollapsingHeader(name.c_str()))
        {
            for (auto itTile = itTileBehavior->second.begin(); itTile != itTileBehavior->second.end(); itTile++)
            {
                auto texture = RessourceManager::GetTexture(itTile->sprite.textureName);
                ImVec2 size = ImVec2(itTile->sprite.size.x / SCALE_FACTOR, itTile->sprite.size.y / SCALE_FACTOR);
                ImVec2 uv0 = ImVec2(itTile->sprite.spriteCoords.x / itTile->sprite.textureSize.x, itTile->sprite.spriteCoords.y / itTile->sprite.textureSize.y); 
                ImVec2 uv1 = ImVec2((itTile->sprite.spriteCoords.x + 1) / itTile->sprite.textureSize.x, (itTile->sprite.spriteCoords.y + 1) / itTile->sprite.textureSize.y); 
                ImGui::Image((ImTextureID)(intptr_t)texture->getID(), size, uv0, uv1);
            }
        }
    }

    ImGui::End();
}