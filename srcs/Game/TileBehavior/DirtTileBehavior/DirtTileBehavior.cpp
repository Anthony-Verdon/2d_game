#include "Game/TileBehavior/DirtTileBehavior/DirtTileBehavior.hpp"
#include "Common/TileBehaviorType.hpp"
#include <iostream>

DirtTileBehavior::DirtTileBehavior(): ATileBehavior()
{
    behaviorType = TileBehaviorType::DIRT;
}

DirtTileBehavior::~DirtTileBehavior()
{
}

void DirtTileBehavior::behavior()
{
    std::cout << "dirt tile behavior" << std::endl;
}