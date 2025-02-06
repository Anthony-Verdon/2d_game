#pragma once

#include "Engine/ATileBehavior/ATileBehavior.hpp"
#include "Engine/Tile/Tile.hpp"
#include <map>

class DirtTileBehavior: public ATileBehavior
{
    private:
        enum Neighbors
        {
            NONE = 0,
            TOP_LEFT = 1 << 0,
            LEFT = 1 << 1,
            BOTTOM_LEFT = 1 << 2,
            TOP = 1 << 3,
            BOTTOM = 1 << 4,
            TOP_RIGHT = 1 << 5,
            RIGHT = 1 << 6,
            BOTTOM_RIGHT = 1 << 7,
        };

        std::map<int, Tile> farmlandTiles;

    public:
        DirtTileBehavior();
        ~DirtTileBehavior();

        void behavior(const std::string &tilemapName, const glm::vec2 &actionCoords);
};