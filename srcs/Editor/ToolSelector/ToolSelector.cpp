#include "Editor/ToolSelector/ToolSelector.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

ToolSelector::ToolSelector()
{
    tools.insert({"Chain Builder", false});
    tools.insert({"Tile Selector", false});
    tools.insert({"Third tool", false});
}

ToolSelector::~ToolSelector()
{
}

void ToolSelector::Draw()
{
    ImGui::Begin("Tool Selector");

    isHoveredOrFocused = ImGui::IsWindowHovered() || ImGui::IsWindowFocused();

    auto checkboxClicked = tools.end();
    auto toolSelected = tools.end();

    for (auto it = tools.begin(); it != tools.end(); it++)
    {
        ImGui::SameLine();
        if (ImGui::Checkbox(it->first.c_str(), &it->second))
            checkboxClicked = it;

        if (it->second)
            toolSelected = it;
        
    }

    if (checkboxClicked != tools.end())
    {
        for (auto it = tools.begin(); it != tools.end(); it++)
        {
            if (it != toolSelected)
                it->second = false;
        }
    }

    if (toolSelected != tools.end())
    {
        ImGui::NewLine();
        ImGui::Text("%s", toolSelected->first.c_str());
    }

    ImGui::End();
}

bool ToolSelector::IsHoveredOrFocused() const
{
    return (isHoveredOrFocused);
}
