#pragma once

#include "Engine/ATileBehavior/ATileBehavior.hpp"
#include "Engine/Tile/Tile.hpp"
#include <map>

class TreeTileBehavior: public ATileBehavior
{
    public:
        TreeTileBehavior();
        ~TreeTileBehavior();

        void behavior(const std::string &tilemapName, const glm::vec2 &actionCoords);
};