#include "Editor/ChainBuilder/ChainBuilder.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <fstream>
#include <nlohmann/json.hpp>
#include <string>
#include "globals.hpp"

ChainBuilder::ChainBuilder(): ATool("Chain Builder")
{
    isBuildingChain = false;
    pointSelected = glm::vec2(-1, -1);
}

ChainBuilder::~ChainBuilder()
{

}

void ChainBuilder::Draw()
{
    if (ImGui::Button("new chain", ImVec2(100, 40)))
    {
        Chain newChain;
        newChain.loop = false;
        chains.push_back(newChain);
        isBuildingChain = true;
    }

    for (auto it = chains.begin(); it != chains.end(); )
    {
        int index = it - chains.begin();
        std::string chainSuffix = "##chain " + std::to_string(index);
        bool closable_group = true;
        if (ImGui::CollapsingHeader(std::to_string(index).c_str(), &closable_group))
        {
            std::string checkboxName = "loop" + chainSuffix;
            ImGui::Checkbox(checkboxName.c_str(), &it->loop);
            for (size_t j = 0; j < it->points.size(); j++)
            {
                std::string pointName = "point " + chainSuffix + "_" + std::to_string(j);
                ImGui::InputFloat2(pointName.c_str(), &it->points[j][0]);
            }
        }

        if (closable_group)
            it++;
        else
            it = chains.erase(it);
    }
}

void ChainBuilder::Load()
{
    if (!std::filesystem::exists("saves/hitbox.json")) // @todo: should be a parameter
        return;
    
    std::ifstream input("saves/hitbox.json");
    nlohmann::json file =  nlohmann::json::parse(input);

    auto itChains = file.find("chains"); //@todo error check
    for (auto itChain : *itChains)
    {
        Chain chain;
        auto itPoints = itChain.find("points"); //@todo error check
        for (auto itPoint : *itPoints)
        {
            chain.points.push_back(glm::vec2(itPoint[0], itPoint[1]));
        }
        chain.loop = itChain["loop"];
        chains.push_back(chain);
    }
}

void ChainBuilder::Save()
{
    nlohmann::json file;

    file["chains"] = {};
    for (size_t i = 0; i < chains.size(); i++)
    {   
        Chain chain = chains[i];
        file["chains"][i]["points"] = {};
        for (size_t j = 0; j < chain.points.size(); j++)
        {
            file["chains"][i]["points"][j] = {chain.points[j].x, chain.points[j].y};
        }
        file["chains"][i]["loop"] = chain.loop;
    }

    std::ofstream o("saves/hitbox.json");
    o << std::setw(4) << file << std::endl;
}

bool ChainBuilder::IsBuildingChain() const
{
    return (isBuildingChain);
}

void ChainBuilder::AddPointToChain(const glm::vec2 &point)
{
    if (isBuildingChain)
        chains[chains.size() - 1].points.push_back(point);
}

void ChainBuilder::SelectPoint(size_t chainIndex, size_t pointIndex)
{
    if (chainIndex >= chains.size())
        return;

    if (pointIndex >= chains[chainIndex].points.size())
        return;

    pointSelected = glm::vec2(chainIndex, pointIndex);
}

void ChainBuilder::UnselectPoint()
{
    pointSelected = glm::vec2(-1, -1);
}

void ChainBuilder::MoveSelectedPoint(const glm::vec2 &position)
{
    if (pointSelected == glm::vec2(-1, -1))
        return;
    chains[pointSelected.x].points[pointSelected.y] = position;
}

void ChainBuilder::CloseChain()
{
    isBuildingChain = false;
}

std::vector<Chain> ChainBuilder::GetChains() const
{
    return (chains);
}