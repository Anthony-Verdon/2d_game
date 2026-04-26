#include "Editor/AnimationCreator/AnimationCreator.hpp"
#include "imgui.h"
#include "globals.hpp"
#include "Engine/RessourceManager/RessourceManager.hpp"
#include <fstream>
#include <filesystem>
#include "Json/Json.hpp"
#include <set>
#include <string>

AnimationCreator::AnimationCreator() : AEditorWindow()
{
    name[0] = 0;
    animationSelected = "";
}

AnimationCreator::~AnimationCreator()
{
}

void AnimationCreator::Draw()
{
    ImGui::Begin("Animation Creator");
    isHoveredOrFocused = ImGui::IsWindowHovered() || ImGui::IsWindowFocused();

    DrawSpriteSelector();
    ImGui::SameLine();
    DrawAnimationsLoader();
    ImGui::SameLine();
    DrawCurrentAnimation();

    ImGui::End();
}

void AnimationCreator::DrawSpriteSelector()
{
    if (ImGui::BeginChild("TilesChild", ImVec2(100, ImGui::GetTextLineHeightWithSpacing() * 8), ImGuiChildFlags_Borders | ImGuiChildFlags_ResizeX | ImGuiChildFlags_ResizeY))
    {
        isHoveredOrFocused |= ImGui::IsWindowHovered() || ImGui::IsWindowFocused();

        // drop text to load texture
        ImGui::Text("drop images here");
        if (ImGui::BeginDragDropTarget())
        {
            if (const ImGuiPayload *payload = ImGui::AcceptDragDropPayload("TEXTURE_SELECTED"))
            {
                std::string data = *(std::string *)payload->Data;
                TextureData newTextureData;
                newTextureData.name = data;
                newTextureData.path = RessourceManager::GetTexture(data)->getPath();
                newTextureData.nbSprite = ml::vec2(1, 1);
                newTextureData.spriteOffset = ml::vec2(0, 0);
                texturesData.push_back(newTextureData);
            }
            ImGui::EndDragDropTarget();
        }

        // setup multi select
        ImGuiMultiSelectFlags flags = ImGuiMultiSelectFlags_ClearOnClickVoid | ImGuiMultiSelectFlags_BoxSelect2d;
        ImGuiMultiSelectIO *ms_io = ImGui::BeginMultiSelect(flags, selection.Size, 1000);
        selection.ApplyRequests(ms_io);

        // start to draw all textures with all their sprites
        // loop over texture loaded and create collapsing header for each one
        // then loop over all the sprites inside the texture and create selectable + image for each one
        size_t SpriteIndex = 0;
        for (auto it = texturesData.begin(); it != texturesData.end();)
        {
            bool closable_group = true;
            if (ImGui::CollapsingHeader(it->name.c_str(), &closable_group))
            {
                std::string nbSpriteInput = "nbSprite###" + std::to_string(it - texturesData.begin());
                if (ImGui::InputFloat2(nbSpriteInput.c_str(), &it->nbSprite[0]))
                    selection.Clear();

                const ImVec2 size = ImVec2(TILE_SIZE * 2.0f, TILE_SIZE * 2.0f);
                for (int j = 0; j < it->nbSprite.y; j++)
                {
                    for (int i = 0; i < it->nbSprite.x; i++)
                    {
                        while (selected.size() <= SpriteIndex)
                            selected.push_back(false);

                        // selectable
                        std::string item = "###" + std::to_string(SpriteIndex);
                        ImVec2 selectable_pos = ImGui::GetCursorScreenPos();
                        ImGui::SetNextItemSelectionUserData(SpriteIndex);
                        if (ImGui::Selectable(item.c_str(), selection.Contains(SpriteIndex), ImGuiSelectableFlags_AllowOverlap, size))
                            selected[SpriteIndex] = !selected[SpriteIndex];
                        // drag drop data
                        if (ImGui::BeginDragDropSource())
                        {
                            CreateDragDropSourceData();
                            ImGui::EndDragDropSource();
                        }

                        // image
                        ImVec2 uv0 = ImVec2((float)i / it->nbSprite.x, (float)j / it->nbSprite.y);
                        ImVec2 uv1 = ImVec2((float)(i + 1) / it->nbSprite.x, (float)(j + 1) / it->nbSprite.y);
                        ImGui::SetCursorScreenPos(selectable_pos);
                        ImGui::Image((ImTextureID)(intptr_t)RessourceManager::GetTexture(it->name)->getID(), size, uv0, uv1);

                        SpriteIndex++;
                        ImGui::SameLine();
                    }
                    ImGui::NewLine();
                }
            }
            else
            {
                SpriteIndex += it->nbSprite.x * it->nbSprite.y;
            }

            if (closable_group)
                it++;
            else
                it = texturesData.erase(it);
        }
        ms_io = ImGui::EndMultiSelect();
        selection.ApplyRequests(ms_io);
    }
    ImGui::EndChild();
}

void AnimationCreator::CreateDragDropSourceData()
{
    if (ImGui::GetDragDropPayload() == NULL)
    {
        tilesSelected.clear();
        void *ptr = NULL;
        ImGuiID id = 0;

        // loop over the selection
        // and determine the texture and the id depending of the texture
        // then add the sprite to the vector
        while (selection.GetNextSelectedItem(&ptr, &id))
        {
            unsigned int nbSprite = 0;
            auto it = texturesData.begin();
            for (; it != texturesData.end(); it++)
            {
                if (id < nbSprite + it->nbSprite.x * it->nbSprite.y)
                {
                    id = id - nbSprite;
                    break;
                }
                nbSprite += it->nbSprite.x * it->nbSprite.y;
            }

            Sprite newSprite;
            newSprite.textureName = it->name;
            newSprite.textureSize = it->nbSprite;
            newSprite.spriteCoords = ml::vec2(id % (int)it->nbSprite.x, id / (int)it->nbSprite.x);
            newSprite.size = ml::vec2(SPRITE_SIZE, SPRITE_SIZE);
            tilesSelected.push_back(newSprite);
        }

        ImGui::SetDragDropPayload("SPRITES_SELECTED", &tilesSelected, sizeof(std::vector<Sprite>));
    }

    const ImGuiPayload *payload = ImGui::GetDragDropPayload();
    std::vector<Sprite> sprites = *(std::vector<Sprite> *)payload->Data;
    ImGui::Text("%zu assets", sprites.size());
}

void AnimationCreator::DrawAnimationsLoader()
{
    if (ImGui::BeginChild("AnimationsChild", ImVec2(100, ImGui::GetTextLineHeightWithSpacing() * 8), ImGuiChildFlags_Borders | ImGuiChildFlags_ResizeX | ImGuiChildFlags_ResizeY))
    {
        isHoveredOrFocused |= ImGui::IsWindowHovered() || ImGui::IsWindowFocused();

        ImGui::InputText("name", name, IM_ARRAYSIZE(name));
        if (ImGui::Button("new animation", ImVec2(100, 40)))
        {
            if (name[0] != 0)
            {
                animations[name] = Animation2D();
                name[0] = 0;
            }
        }
        int index = 0;
        for (auto it = animations.begin(); it != animations.end();)
        {
            ImGui::SetNextItemAllowOverlap();
            if (ImGui::Selectable(it->first.c_str(), it->first == animationSelected))
                animationSelected = it->first;
            ImGui::SameLine();
            std::string button = "X###" + std::to_string(index);
            if (ImGui::SmallButton(button.c_str()))
                it = animations.erase(it);
            else
                it++;
            index++;
        }
    }
    ImGui::EndChild();
}

void AnimationCreator::DrawCurrentAnimation()
{
    ImVec2 ChildPos = ImGui::GetCursorScreenPos();
    if (ImGui::BeginChild("ResizableChild", ImVec2(100, ImGui::GetTextLineHeightWithSpacing() * 8), ImGuiChildFlags_Borders | ImGuiChildFlags_ResizeX | ImGuiChildFlags_ResizeY))
    {
        isHoveredOrFocused |= ImGui::IsWindowHovered() || ImGui::IsWindowFocused();

        std::vector<Sprite> frames;
        if (animationSelected != "")
            frames = animations[animationSelected].GetFrames();

        // needed to be able to swap selectables easily
        int frameIndexSize = frameIndex.size();
        int diff = frames.size() - frameIndexSize;
        if (diff > 0)
        {
            for (int i = 0; i < diff; i++)
                frameIndex.push_back(frameIndexSize + i);
        }

        const ImVec2 size = ImVec2(TILE_SIZE * 2.0f, TILE_SIZE * 2.0f);
        ImGui::PushItemFlag(ImGuiItemFlags_AllowDuplicateId, true);
        for (size_t i = 0; i < frames.size(); i++)
        {
            ImGui::SameLine();

            ImVec2 uv0 = ImVec2(1.0f / frames[i].textureSize.x * frames[i].spriteCoords.x, 1.0f / frames[i].textureSize.y * frames[i].spriteCoords.y);
            ImVec2 uv1 = ImVec2(1.0f / frames[i].textureSize.x * (frames[i].spriteCoords.x + 1), 1.0f / frames[i].textureSize.y * (frames[i].spriteCoords.y + 1));
            ImVec2 selectable_pos = ImGui::GetCursorScreenPos();

            ImGui::Selectable(std::to_string(frameIndex[i]).c_str(), false, ImGuiSelectableFlags_AllowOverlap, size);
            if (ImGui::IsItemActive() && !ImGui::IsItemHovered())
            {
                int i_next = i + (ImGui::GetMouseDragDelta(0).x < 0.f ? -1 : 1);
                if (i_next >= 0 && i_next < (int)frames.size())
                {
                    std::swap(frames[i], frames[i_next]);
                    std::swap(frameIndex[i], frameIndex[i_next]);
                    ImGui::ResetMouseDragDelta();
                }
            }
            ImGui::SetCursorScreenPos(selectable_pos);
            ImGui::Image((ImTextureID)(intptr_t)RessourceManager::GetTexture(frames[i].textureName)->getID(), size, uv0, uv1);
        }
        ImGui::PopItemFlag();
        if (animationSelected != "")
            animations[animationSelected].SetFrames(frames);
    }
    ImGui::EndChild();
    if (ImGui::BeginDragDropTarget())
    {
        if (const ImGuiPayload *payload = ImGui::AcceptDragDropPayload("SPRITES_SELECTED"))
        {
            std::vector<Sprite> sprites = *(std::vector<Sprite> *)payload->Data;
            if (animationSelected != "")
            {
                for (size_t i = 0; i < sprites.size(); i++)
                    animations[animationSelected].AddFrame(sprites[i]);
            }
        }
        ImGui::EndDragDropTarget();
    }

    ImVec2 childSize = ImGui::GetItemRectSize();
    ChildPos.y += childSize.y + ImGui::GetTextLineHeightWithSpacing();
    ImGui::SetCursorScreenPos(ChildPos);
    if (animationSelected != "")
    {
        bool isStoppable = animations[animationSelected].IsStoppable();
        ImGui::Checkbox("Stoppable", &isStoppable);
        animations[animationSelected].SetStoppable(isStoppable);
    }
}

void AnimationCreator::Load()
{
    if (!std::filesystem::exists("saves/animations.json")) // @todo: should be a parameter
        return;

    Json::Node file = Json::ParseFile("saves/animations.json");

    if (file.KeyExist("textures") && file["textures"] != nullptr)
    {
        for (auto it : file["textures"])
        {
            RessourceManager::AddTexture(it["name"], it["path"]);
        }
    }

    if (file.KeyExist("animationsPath") && file["animationsPath"] != nullptr)
    {
        for (auto it : file["animationsPath"])
        {
            std::string path = std::string(it); // @PROBLEM?
            Animation2D newAnimation;

            auto itAnimation = file[std::string("/animations/" + path).c_str()];
            if (itAnimation.KeyExist("frames") && itAnimation["frames"] != nullptr)
            {

                for (auto itFrame : itAnimation["frames"])
                {
                    Sprite newFrame;
                    newFrame.textureName = std::string(itFrame["texture"]["name"]);
                    newFrame.textureSize = {itFrame["texture"]["size"][0], itFrame["texture"]["size"][1]};
                    newFrame.spriteCoords = {itFrame["position"][0], itFrame["position"][1]};
                    newAnimation.AddFrame(newFrame);
                }

                newAnimation.SetStoppable(itAnimation["stoppable"]);
                animations[path] = newAnimation;
            }
        }
    }
}

void AnimationCreator::Save()
{
    Json::Node file;
    file["textures"] = {};
    std::set<std::string> textures;
    std::set<std::string> animationsPath;

    file["animations"] = {};
    for (auto it = animations.begin(); it != animations.end(); it++)
    {
        file["animations"][std::string("/" + it->first).c_str()]["frames"] = {};
        std::vector<Sprite> animationFrames = it->second.GetFrames();
        for (size_t j = 0; j < animationFrames.size(); j++)
        {
            file["animations"][std::string("/" + it->first).c_str()]["frames"][j]["texture"]["name"] = animationFrames[j].textureName;
            file["animations"][std::string("/" + it->first).c_str()]["frames"][j]["texture"]["size"][0] = animationFrames[j].textureSize.x;
            file["animations"][std::string("/" + it->first).c_str()]["frames"][j]["texture"]["size"][1] = animationFrames[j].textureSize.y;
            file["animations"][std::string("/" + it->first).c_str()]["frames"][j]["position"][0] = animationFrames[j].spriteCoords.x;
            file["animations"][std::string("/" + it->first).c_str()]["frames"][j]["position"][1] = animationFrames[j].spriteCoords.y;
            textures.insert(animationFrames[j].textureName);
        }
        file["animations"][std::string("/" + it->first).c_str()]["stoppable"] = it->second.IsStoppable();
        animationsPath.insert(it->first);
    }

    int i = 0;
    for (auto it = textures.begin(); it != textures.end(); it++)
    {
        file["textures"][i]["name"] = *it;
        file["textures"][i]["path"] = RessourceManager::GetTexture(*it)->getPath();

        i++;
    }

    i = 0;
    for (auto it = animationsPath.begin(); it != animationsPath.end(); it++)
    {
        file["animationsPath"][i] = *it;

        i++;
    }

    std::ofstream o("saves/animations.json");
    o << std::setw(4) << file << std::endl;
}
