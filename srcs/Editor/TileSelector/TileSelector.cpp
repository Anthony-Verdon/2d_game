#include "Editor/TileSelector/TileSelector.hpp"
#include "Engine/RessourceManager/RessourceManager.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "globals.hpp"
#include <fstream>
#include <nlohmann/json.hpp>

TileSelector::TileSelector()
{
    name[0] = 0;
    path[0] = 0;
    nbSprite = glm::vec2(0, 0);

    tileSelected.textureName = "";
}

TileSelector::~TileSelector()
{
}

void TileSelector::Draw()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGui::Begin("Tile Selector");

    isHoveredOrFocused = ImGui::IsWindowHovered() || ImGui::IsWindowFocused();

    InputFields();
    TilesAdded();

    ImGui::End();
}

void TileSelector::InputFields()
{
    ImGui::InputText("name", name, IM_ARRAYSIZE(name));
    ImGui::InputText("path", path, IM_ARRAYSIZE(path));
    ImGui::InputFloat("nbSprite x", &nbSprite.x, 1, 128, "%.3f");
    ImGui::InputFloat("nbSprite y", &nbSprite.y, 1, 128, "%.3f");

    if (ImGui::Button("new texture", ImVec2(100, 40)))
    {
        TextureData data;
        data.name = name;
        data.path = path;
        data.nbSprite = nbSprite;
        texturesData.push_back(data);
        
        RessourceManager::AddTexture(name, path);

        name[0] = 0;
        path[0] = 0;
        nbSprite = glm::vec2(0, 0);
    }
}

void TileSelector::TilesAdded()
{
    for (size_t x = 0; x < texturesData.size(); x++)
    {
        std::string textureName = texturesData[x].name;
        if (ImGui::CollapsingHeader(textureName.c_str()))
        {
            glm::vec2 textureSize = texturesData[x].nbSprite;
            ImVec2 size = ImVec2(TILE_SIZE * 2.0f, TILE_SIZE * 2.0f);
            ImVec4 bg_col = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
            ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
            for (int j = 0; j < textureSize.y; j++)
            {
                for (int i = 0; i < textureSize.x; i++)
                {
                    ImVec2 uv0 = ImVec2((float)i / textureSize.x,(float)j / textureSize.y); 
                    ImVec2 uv1 = ImVec2((float)(i + 1) / textureSize.x, (float)(j + 1) / textureSize.y);
                    std::string button = std::to_string(j) + "_" + std::to_string(i);
                    if (ImGui::ImageButton(button.c_str(), (ImTextureID)(intptr_t)RessourceManager::GetTexture(textureName)->getID(), size, uv0, uv1, bg_col, tint_col))
                    {
                        tileSelected.textureName = textureName; 
                        tileSelected.textureSize = textureSize; 
                        tileSelected.spriteCoords = glm::vec2(i, j); 
                    }
                    ImGui::SameLine();
                }
                ImGui::NewLine();
            }
        }
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
        i++;
    }

    std::ofstream o("saves/textures.json");
    o << std::setw(4) << file << std::endl;
}

Sprite TileSelector::GetTile() const
{
    return (tileSelected);
}

bool TileSelector::IsHoveredOrFocused() const
{
    return (isHoveredOrFocused);
}