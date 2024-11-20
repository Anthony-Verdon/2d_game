#include "Editor/ChainBuilder/ChainBuilder.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <fstream>
#include <nlohmann/json.hpp>
#include <string>

ChainBuilder::ChainBuilder()
{
    isBuildingChain = false;
}

ChainBuilder::~ChainBuilder()
{

}

void ChainBuilder::Draw()
{
    ImGui::Begin("Chain Builder");

    isHoveredOrFocused = ImGui::IsWindowHovered() || ImGui::IsWindowFocused();

    if (ImGui::Button("new chain", ImVec2(100, 40)))
    {
        chains.push_back({});
        isBuildingChain = true;
    }

    for (size_t i = 0; i < chains.size(); i++)
    {
        if (ImGui::CollapsingHeader(std::to_string(i).c_str()))
        {
            std::vector<glm::vec2> chain = chains[i];
            for (size_t j = 0; j < chain.size(); j++)
            {
                ImGui::Text("point %zu: (%g, %g)", j, chain[j].x, chain[j].y);
            }
        }
    }

    ImGui::End();
}

bool ChainBuilder::IsHoveredOrFocused() const
{
    return (isHoveredOrFocused);
}

bool ChainBuilder::IsBuildingChain() const
{
    return (isBuildingChain);
}

void ChainBuilder::AddPointToChain(const glm::vec2 &point)
{
    chains[chains.size() - 1].push_back(point);
}
void ChainBuilder::CloseChain()
{
    isBuildingChain = false;
}

std::vector<std::vector<glm::vec2>> ChainBuilder::GetChains() const
{
    return (chains);
}