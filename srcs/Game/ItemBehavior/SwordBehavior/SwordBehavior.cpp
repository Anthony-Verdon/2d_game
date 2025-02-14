#include "Game/ItemBehavior/SwordBehavior/SwordBehavior.hpp"

SwordBehavior::SwordBehavior()
{
    toolType = PlayerTool::SWORD;
}

SwordBehavior::~SwordBehavior()
{
}

#include <iostream>
void SwordBehavior::MainAction(const glm::vec2 &actionCoords)
{
    (void)actionCoords;
    std::cout << "use sword" << std::endl;
}