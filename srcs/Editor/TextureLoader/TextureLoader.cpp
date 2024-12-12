#include "Editor\TextureLoader\TextureLoader.hpp"
#include "Engine/RessourceManager/RessourceManager.hpp"
#include "imgui.h"

TextureLoader::TextureLoader()
{
    name[0] = 0;
    path[0] = 0;
}

TextureLoader::~TextureLoader()
{
}

void TextureLoader::Draw()
{
    ImGui::Begin("Texture Loader");

    isHoveredOrFocused = ImGui::IsWindowHovered() || ImGui::IsWindowFocused();

    ImGui::InputText("name", name, IM_ARRAYSIZE(name));
    ImGui::InputText("path", path, IM_ARRAYSIZE(path));
    if (ImGui::BeginDragDropTarget())
    {
        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("FILE_EXPLORER_SELECTED_DATA"))
        {
            std::string data = *(std::string*)payload->Data;
            std::memset(path, 0, INPUT_ARRAY_SIZE);
            std::memcpy(path, data.c_str(), data.size() % INPUT_ARRAY_SIZE);
        }
        ImGui::EndDragDropTarget();
    }

    if (ImGui::Button("new texture", ImVec2(100, 40)))
    {
        textures.push_back(name);
        RessourceManager::AddTexture(name, path);

        name[0] = 0;
        path[0] = 0;
    }

    for (size_t i = 0; i < textures.size(); i++)
    {
        if (ImGui::CollapsingHeader(textures[i].c_str()))
        {
            std::shared_ptr<Texture> texture = RessourceManager::GetTexture(textures[i]);
            ImGui::ImageButton("", (ImTextureID)(intptr_t)texture->getID(), ImVec2(texture->getWidth(), texture->getHeight()));
            if (ImGui::BeginDragDropSource())
            {
                ImGui::SetDragDropPayload("TEXTURE_SELECTED", &textures[i], sizeof(std::string));
                ImGui::Text("%s", textures[i].c_str());
                ImGui::EndDragDropSource();
            }
        }

    }
    ImGui::End();
}

bool TextureLoader::IsHoveredOrFocused() const
{
    return (isHoveredOrFocused);
}