#include "Game/PlayerTools/Pickaxe/Pickaxe.hpp"
#include "Engine/TilemapManager/TilemapManager.hpp"

Pickaxe::Pickaxe()
{
    toolType = PlayerTool::PICKAXE;
}

Pickaxe::~Pickaxe()
{
}

#include <iostream>
void Pickaxe::MainAction(const glm::vec2 &actionCoords)
{
    std::cout << "use pickaxe" << std::endl;
    TilemapManager::SuppressTile("b", actionCoords);
}