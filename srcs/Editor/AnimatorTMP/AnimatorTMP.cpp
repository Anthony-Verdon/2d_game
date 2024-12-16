#include "Editor/AnimatorTMP/AnimatorTMP.hpp"
#include "imgui.h"
#include "globals.hpp"
#include "Engine/RessourceManager/RessourceManager.hpp"

AnimatorTMP::AnimatorTMP()
{
    name[0] = 0;
    animationSelected = "";
}

AnimatorTMP::~AnimatorTMP()
{
}

#include <iostream>
void AnimatorTMP::Draw()
{
    ImGui::Begin("Animator TMP");
    isHoveredOrFocused = ImGui::IsWindowHovered() || ImGui::IsWindowFocused();

    if (ImGui::BeginChild("TilesChild", ImVec2(100, ImGui::GetTextLineHeightWithSpacing() * 8), ImGuiChildFlags_Borders | ImGuiChildFlags_ResizeX))
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
            
                ImVec2 size = ImVec2(TILE_SIZE * 2.0f, TILE_SIZE * 2.0f);
                ImVec4 bg_col = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
                ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
                for (int j = 0; j < it->nbSprite.y; j++)
                {
                    for (int i = 0; i < it->nbSprite.x; i++)
                    {
                        ImVec2 uv0 = ImVec2((float)i / it->nbSprite.x,(float)j / it->nbSprite.y); 
                        ImVec2 uv1 = ImVec2((float)(i + 1) / it->nbSprite.x, (float)(j + 1) / it->nbSprite.y);
                        std::string button = std::to_string(index) + "_" + std::to_string(j) + "_" + std::to_string(i);
                        if (ImGui::ImageButton(button.c_str(), (ImTextureID)(intptr_t)RessourceManager::GetTexture(it->name)->getID(), size, uv0, uv1, bg_col, tint_col))
                        {
                            tileSelected.textureName = it->name; 
                            tileSelected.textureSize = it->nbSprite; 
                            tileSelected.spriteCoords = glm::vec2(i, j); 
                            tileSelected.size = glm::vec2(SPRITE_SIZE, SPRITE_SIZE) * it->spriteScale;
                        }
                        if (ImGui::BeginDragDropSource())
                        {
                            tileSelected.textureName = it->name; 
                            tileSelected.textureSize = it->nbSprite; 
                            tileSelected.spriteCoords = glm::vec2(i, j); 
                            tileSelected.size = glm::vec2(SPRITE_SIZE, SPRITE_SIZE) * it->spriteScale;
                            ImGui::SetDragDropPayload("TILE_SELECTED", &tileSelected, sizeof(Sprite));
                            ImGui::Text("");
                            ImGui::EndDragDropSource();
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
    ImGui::EndChild();
    ImGui::SameLine();

    if (ImGui::BeginChild("AnimationsChild", ImVec2(100, ImGui::GetTextLineHeightWithSpacing() * 8), ImGuiChildFlags_Borders | ImGuiChildFlags_ResizeX))
    {   
        ImGui::InputText("name", name, IM_ARRAYSIZE(name));
        if (ImGui::Button("new animation", ImVec2(100, 40)))
        {
            if (name[0] != 0)
            {
                animations[name] = Animation();
                name[0] = 0;
            }
        }
        ImGui::ShowDemoWindow();
        for (auto it = animations.begin(); it != animations.end(); it++)
        {
            if (ImGui::Selectable(it->first.c_str(), it->first == animationSelected))
                animationSelected = it->first;
        }

    }
    ImGui::EndChild();
    ImGui::SameLine();
    if (ImGui::BeginChild("ResizableChild", ImVec2(100, ImGui::GetTextLineHeightWithSpacing() * 8), ImGuiChildFlags_Borders | ImGuiChildFlags_ResizeX))
    {

        std::vector<Sprite> frames;
        if (animationSelected != "")
            frames = animations[animationSelected].GetFrames();

        ImVec2 size = ImVec2(TILE_SIZE * 2.0f, TILE_SIZE * 2.0f);
        ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
        for (size_t i = 0; i < frames.size(); i++)
        {
            ImVec2 uv0 = ImVec2(1.0f / frames[i].textureSize.x * frames[i].spriteCoords.x, 1.0f / frames[i].textureSize.y * frames[i].spriteCoords.y); 
            ImVec2 uv1 = ImVec2(1.0f / frames[i].textureSize.x * (frames[i].spriteCoords.x + 1), 1.0f / frames[i].textureSize.y * (frames[i].spriteCoords.y + 1));
            ImGui::SameLine();
            ImGui::Image((ImTextureID)(intptr_t)RessourceManager::GetTexture(frames[i].textureName)->getID(), size, uv0, uv1, tint_col, ImGui::GetStyleColorVec4(ImGuiCol_Border));
        }
    }
    ImGui::EndChild();
    if (ImGui::BeginDragDropTarget())
    {
        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("TILE_SELECTED"))
        {
            Sprite sprite = *(Sprite*)payload->Data;
            if (animationSelected != "")
                animations[animationSelected].AddFrame(sprite);
        }
        ImGui::EndDragDropTarget();
    }

    ImGui::End();
}

bool AnimatorTMP::IsHoveredOrFocused() const
{
    return (isHoveredOrFocused);
}