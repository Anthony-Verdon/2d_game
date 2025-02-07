#pragma once

#include "Engine/ATileBehavior/ATileBehavior.hpp"
#include "Engine/Tile/Tile.hpp"
#include <map>

class RockTileBehavior: public ATileBehavior
{
    public:
        RockTileBehavior();
        ~RockTileBehavior();

        void behavior(const std::string &tilemapName, const glm::vec2 &actionCoords);
};