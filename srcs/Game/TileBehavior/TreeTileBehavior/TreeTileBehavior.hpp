#pragma once

#include "Engine/2D/ATileBehavior/ATileBehavior.hpp"
#include "Engine/2D/Tile/Tile.hpp"
#include <map>

class TreeTileBehavior: public ATileBehavior
{
    public:
        TreeTileBehavior();
        ~TreeTileBehavior();

        void behavior(const std::string &tilemapName, const glm::vec2 &actionCoords);
};