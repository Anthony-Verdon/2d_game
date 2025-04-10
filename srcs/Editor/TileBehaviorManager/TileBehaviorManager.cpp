#include "Editor/TileBehaviorManager/TileBehaviorManager.hpp"
#include "imgui.h"
#include <magic_enum.hpp>
#include <iostream>
#include "Engine/RessourceManager/RessourceManager.hpp"
#include "Engine/2D/TileDictionnary/TileDictionnary.hpp"
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


void TileBehaviorManager::Load()
{
    for (size_t i = 0; i < TileDictionnary::GetDictionnarySize(); i++)
    {
        Tile tile = TileDictionnary::GetTile(i);
        tile.sprite.size = tile.sprite.size / SCALE_FACTOR;
        for (size_t j = 0; j < tile.behaviors.size(); j++)
            tilesBehavior[tile.behaviors[j]].push_back(tile);
    }
}

void TileBehaviorManager::Draw()
{
    ImGui::Begin("Tile Behavior Manager");

    isHoveredOrFocused = ImGui::IsWindowHovered() || ImGui::IsWindowFocused();

    size_t buttonIndex = 0;
    for (auto itTileBehavior = tilesBehavior.begin(); itTileBehavior != tilesBehavior.end(); itTileBehavior++)
    {
        std::string name = std::string(magic_enum::enum_name(itTileBehavior->first).data());
        if (ImGui::CollapsingHeader(name.c_str()))
        {
            ImGui::Text("drop tiles here");
            if (ImGui::BeginDragDropTarget())
            {
                if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("TILES_SELECTED"))
                {
                    std::vector<Tile> tiles = *(std::vector<Tile>*)payload->Data;
                    for (size_t i = 0; i < tiles.size(); i++)
                    {
                        if (std::find(itTileBehavior->second.begin(), itTileBehavior->second.end(), tiles[i]) != itTileBehavior->second.end())
                            continue;
                        
                        size_t j = 0;
                        for (; j < itTileBehavior->second.size(); j++)
                        {
                            if (tiles[i].sprite.size.y < itTileBehavior->second[j].sprite.size.y)
                            {
                                itTileBehavior->second.insert(itTileBehavior->second.begin() + j, tiles[i]);
                                break;
                            }
                        }
                        
                        if (j == 0 || j == itTileBehavior->second.size())
                            itTileBehavior->second.push_back(tiles[i]);
                        
                        Tile copy = tiles[i];
                        copy.sprite.size = copy.sprite.size * SCALE_FACTOR;
                        size_t index = TileDictionnary::AddTile(copy);
                        TileDictionnary::AddTileBehavior(index, itTileBehavior->first);
                    }
                }
                ImGui::EndDragDropTarget();
            }

            size_t lastTileHeight = 0;
            bool firstTile = true;
            for (auto itTile = itTileBehavior->second.begin(); itTile != itTileBehavior->second.end();)
            {
                auto texture = RessourceManager::GetTexture(itTile->sprite.textureName);
                ImVec2 size = ImVec2(itTile->sprite.size.x, itTile->sprite.size.y);
                ImVec2 uv0 = ImVec2(itTile->sprite.spriteCoords.x / itTile->sprite.textureSize.x, itTile->sprite.spriteCoords.y / itTile->sprite.textureSize.y); 
                ImVec2 uv1 = ImVec2((itTile->sprite.spriteCoords.x + 1) / itTile->sprite.textureSize.x, (itTile->sprite.spriteCoords.y + 1) / itTile->sprite.textureSize.y); 
                std::string button = "###" + std::to_string(buttonIndex);

                if (!firstTile && lastTileHeight == size.y)
                {
                    ImGui::SameLine();
                    ImVec2 sizeAvailable =  ImGui::GetContentRegionAvail();
                    if (sizeAvailable.x <= size.x)
                        ImGui::NewLine();
                }

                if (ImGui::ImageButton(button.c_str(), (ImTextureID)(intptr_t)texture->getID(), size, uv0, uv1))
                {
                    Tile copy = *itTile;
                    copy.sprite.size = copy.sprite.size * SCALE_FACTOR;
                    size_t index = TileDictionnary::GetTileIndex(copy);
                    TileDictionnary::RemoveTileBehavior(index, itTileBehavior->first);
                    itTile = itTileBehavior->second.erase(itTile);
                }
                else
                    itTile++;
                
                lastTileHeight = size.y;
                firstTile = false;
                buttonIndex++;
            }
        }
        else
        {
            buttonIndex += itTileBehavior->second.size();
        }
    }

    ImGui::End();
}