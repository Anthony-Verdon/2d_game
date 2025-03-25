#pragma once

#include "Engine/2D/ATileBehavior/ATileBehavior.hpp"
#include "Engine/2D/Tile/Tile.hpp"
#include <map>

class RockTileBehavior: public ATileBehavior
{
    public:
        RockTileBehavior();
        ~RockTileBehavior();

        void behavior(const std::string &tilemapName, const glm::vec2 &actionCoords);
};