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
        chains.push_back({});
        isBuildingChain = true;
    }

    for (size_t i = 0; i < chains.size(); i++)
    {
        if (ImGui::CollapsingHeader(std::to_string(i).c_str()))
        {
            std::vector<glm::vec2> &chain = chains[i];
            for (size_t j = 0; j < chain.size(); j++)
            {
                std::string name = "point " + std::to_string(j);
                ImGui::InputFloat2(name.c_str(), &chain[j][0]);
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
        std::vector<glm::vec2> chain;
        auto itPoints = itChain.find("points"); //@todo error check
        for (auto itPoint : *itPoints)
        {
            chain.push_back(glm::vec2(itPoint[0], itPoint[1]));
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
        std::vector<glm::vec2> chain = chains[i];
        for (size_t j = 0; j < chain.size(); j++)
        {
            file["chains"][i]["points"][j] = {chain[j].x, chain[j].y};
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