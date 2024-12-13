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