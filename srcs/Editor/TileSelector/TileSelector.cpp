#include "Editor/TileSelector/TileSelector.hpp"
#include "Editor/AnimationCreator/AnimationCreator.hpp"
#include "Engine/RessourceManager/RessourceManager.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "globals.hpp"
#include <fstream>
#include <nlohmann/json.hpp>

TileSelector::TileSelector(): ATool("Tile Selector")
{
    tileSelected.textureName = "";
}

TileSelector::~TileSelector()
{
}

void TileSelector::Draw()
{
    InputFields();
    TilesAdded();
}

void TileSelector::InputFields()
{
    ImGui::Text("drop images here");
    if (ImGui::BeginDragDropTarget())
    {
        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("TEXTURE_SELECTED"))
        {
            std::string data = *(std::string*)payload->Data;
            TextureData newTextureData;
            newTextureData.name = data;
            newTextureData.path = RessourceManager::GetTexture(data)->getPath();
            newTextureData.nbSprite = glm::vec2(1, 1);
            newTextureData.spriteScale = 1;
            texturesData.push_back(newTextureData);
        }
        ImGui::EndDragDropTarget();
    }
}

void TileSelector::TilesAdded()
{
    for (auto it = texturesData.begin(); it != texturesData.end(); )
    {
        bool closable_group = true;
        if (ImGui::CollapsingHeader(it->name.c_str(), &closable_group))
        {
            int index = it - texturesData.begin();
            std::string nbSpriteInput = "nbSprite###" + std::to_string(index);
            std::string scaleInput = "scale###" + std::to_string(index);
            ImGui::InputFloat2(nbSpriteInput.c_str(), &it->nbSprite[0]);
            if (ImGui::InputFloat(scaleInput.c_str(), &it->spriteScale, 1, 128, "%.3f"))
            {
                tileSelected.size = glm::vec2(SPRITE_SIZE, SPRITE_SIZE) * it->spriteScale;
            }
        
            ImVec4 bg_col = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
            ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
            for (int j = 0; j < it->nbSprite.y; j++)
            {
                for (int i = 0; i < it->nbSprite.x; i++)
                {
                    auto texture = RessourceManager::GetTexture(it->name);
                    ImVec2 uv0 = ImVec2((float)i / it->nbSprite.x,(float)j / it->nbSprite.y); 
                    ImVec2 uv1 = ImVec2((float)(i + 1) / it->nbSprite.x, (float)(j + 1) / it->nbSprite.y);
                    std::string button = std::to_string(index) + "_" + std::to_string(j) + "_" + std::to_string(i);
                    glm::vec2 size = glm::vec2(texture->getWidth() / it->nbSprite.x, texture->getHeight() / it->nbSprite.y);
                    if (ImGui::ImageButton(button.c_str(), (ImTextureID)(intptr_t)texture->getID(), ImVec2(size.x, size.y), uv0, uv1, bg_col, tint_col))
                    {
                        tileSelected.textureName = it->name; 
                        tileSelected.textureSize = it->nbSprite; 
                        tileSelected.spriteCoords = glm::vec2(i, j); 
                        tileSelected.size = size * SCALE_FACTOR;
                    }
                    ImGui::SameLine();
                }
                ImGui::NewLine();
            }
        }
        if (closable_group)
            it++;
        else
            it = texturesData.erase(it);
    }
}

void TileSelector::Load()
{
    if (!std::filesystem::exists("saves/textures.json")) // @todo: should be a parameter
        return;
    
    std::ifstream input("saves/textures.json");
    nlohmann::json file =  nlohmann::json::parse(input);

    auto itTextures = file.find("textures"); //@todo error check
    for (auto it : *itTextures)
    {
        TextureData data;
        data.name = it["name"];
        data.path = it["path"];
        data.nbSprite = glm::vec2(it["nbSprite"][0], it["nbSprite"][1]);
        data.spriteScale = it["scale"];
        texturesData.push_back(data);
        RessourceManager::AddTexture(data.name, data.path);
    }
}

void TileSelector::Save()
{
    nlohmann::json file;

    file["textures"] = {};
    int i = 0;
    for (auto it = texturesData.begin(); it != texturesData.end(); it++)
    {
        file["textures"][i]["name"] = it->name;
        file["textures"][i]["path"] = it->path;
        file["textures"][i]["nbSprite"] = {it->nbSprite.x, it->nbSprite.y};
        file["textures"][i]["scale"] = it->spriteScale;
        i++;
    }

    std::ofstream o("saves/textures.json");
    o << std::setw(4) << file << std::endl;
}

Sprite TileSelector::GetSprite() const
{
    return (tileSelected);
}