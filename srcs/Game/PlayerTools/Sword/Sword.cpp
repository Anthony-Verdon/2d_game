#include "Game/PlayerTools/Sword/Sword.hpp"

Sword::Sword()
{
    toolType = PlayerTool::SWORD;
}

Sword::~Sword()
{
}

#include <iostream>
void Sword::MainAction()
{
    std::cout << "use sword" << std::endl;
}