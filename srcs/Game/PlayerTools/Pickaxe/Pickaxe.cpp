#include "Game/PlayerTools/Pickaxe/Pickaxe.hpp"

Pickaxe::Pickaxe()
{
    toolType = PlayerTool::PICKAXE;
}

Pickaxe::~Pickaxe()
{
}

#include <iostream>
void Pickaxe::MainAction()
{
    std::cout << "use pickaxe" << std::endl;
}