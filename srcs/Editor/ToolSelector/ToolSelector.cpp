#include "Editor/ToolSelector/ToolSelector.hpp"
#include "Editor/TileSelector/TileSelector.hpp"
#include "Editor/ChainBuilder/ChainBuilder.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

ToolSelector::ToolSelector(): AEditorWindow()
{
    tools.insert({std::make_shared<TileSelector>(), false});
    tools.insert({std::make_shared<ChainBuilder>(), false});

    for (auto it = tools.begin(); it != tools.end(); it++)
        it->first->Load();
}

ToolSelector::~ToolSelector()
{
    for (auto it = tools.begin(); it != tools.end(); it++)
        it->first->Save();
}

void ToolSelector::Draw()
{
    ImGui::Begin("Tool Selector");

    isHoveredOrFocused = ImGui::IsWindowHovered() || ImGui::IsWindowFocused();
    toolSelected = tools.end();

    for (auto it = tools.begin(); it != tools.end(); it++)
    {
        ImGui::SameLine();
        if (ImGui::Checkbox(it->first->GetName().c_str(), &it->second) && it->second)
        {
            toolSelected = it;
            for (auto it2 = tools.begin(); it2 != tools.end(); it2++)
            {
                if (it2 != it)
                    it2->second = false;
            }
            break;
        }

        if (it->second)
            toolSelected = it;
    }

    if (toolSelected != tools.end())
    {
        ImGui::NewLine();
        toolSelected->first->Draw();
    }

    ImGui::End();
}

std::shared_ptr<ATool> ToolSelector::GetSelectedTool() const
{
    if (toolSelected == tools.end())
        return (NULL);
    else
        return (toolSelected->first);
}