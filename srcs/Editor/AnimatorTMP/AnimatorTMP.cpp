#include "Editor/AnimatorTMP/AnimatorTMP.hpp"
#include "imgui.h"
#include "globals.hpp"
#include "Engine/RessourceManager/RessourceManager.hpp"

AnimatorTMP::AnimatorTMP()
{
}

AnimatorTMP::~AnimatorTMP()
{
}

void AnimatorTMP::Draw()
{
    ImGui::Begin("Animator TMP");
    isHoveredOrFocused = ImGui::IsWindowHovered() || ImGui::IsWindowFocused();

    if (ImGui::BeginChild("ResizableChild", ImVec2(-100, ImGui::GetTextLineHeightWithSpacing() * 8), ImGuiChildFlags_Borders | ImGuiChildFlags_ResizeX))
    {
        ImVec2 size = ImVec2(TILE_SIZE * 2.0f, TILE_SIZE * 2.0f);
        ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
        for (size_t i = 0; i < sprites.size(); i++)
        {
            ImGui::SameLine();
            ImGui::Image((ImTextureID)(intptr_t)RessourceManager::GetTexture(sprites[i].textureName)->getID(), size, sprites[i].uv0, sprites[i].uv1, tint_col, ImGui::GetStyleColorVec4(ImGuiCol_Border));
        }
    }
    ImGui::EndChild();
    if (ImGui::BeginDragDropTarget())
    {
        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("TILE_SELECTED"))
        {
            textureTMP sprite = *(textureTMP*)payload->Data;
            sprites.push_back(sprite);
        }
        ImGui::EndDragDropTarget();
    }

    ImGui::End();
}

bool AnimatorTMP::IsHoveredOrFocused() const
{
    return (isHoveredOrFocused);
}