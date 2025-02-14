#include "Game/Items/ItemBehavior/SwordBehavior/SwordBehavior.hpp"

SwordBehavior::SwordBehavior()
{
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