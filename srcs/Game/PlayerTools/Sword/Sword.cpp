#include "Game/PlayerTools/Sword/Sword.hpp"

Sword::Sword()
{
    toolType = PlayerTool::SWORD;
}

Sword::~Sword()
{
}

#include <iostream>
void Sword::MainAction(const glm::vec2 &actionCoords)
{
    (void)actionCoords;
    std::cout << "use sword" << std::endl;
}