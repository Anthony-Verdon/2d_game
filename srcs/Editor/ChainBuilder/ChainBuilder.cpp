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
}

ChainBuilder::~ChainBuilder()
{

}

void ChainBuilder::Draw()
{
    if (ImGui::Button("new chain", ImVec2(100, 40)))
    {
        Chain newChain;
        chains.push_back(newChain);
        isBuildingChain = true;
    }

    for (size_t i = 0; i < chains.size(); i++)
    {
        if (ImGui::CollapsingHeader(std::to_string(i).c_str()))
        {
            Chain &chain = chains[i];
            for (size_t j = 0; j < chain.points.size(); j++)
            {
                std::string name = "point " + std::to_string(j) + "##chain " + std::to_string(i);
                ImGui::InputFloat2(name.c_str(), &chain.points[j][0]);
            }
        }
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
        for (size_t j = 0; j < chain.points.size(); j++)
        {
            file["chains"][i]["points"][j] = {chain.points[j].x, chain.points[j].y};
        }
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
void ChainBuilder::CloseChain()
{
    isBuildingChain = false;
}

std::vector<Chain> ChainBuilder::GetChains() const
{
    return (chains);
}