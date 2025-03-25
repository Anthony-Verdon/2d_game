#pragma once

#include "Engine/2D/ATileBehavior/ATileBehavior.hpp"
#include "Engine/2D/Tile/Tile.hpp"
#include <map>

class DirtTileBehavior: public ATileBehavior
{
    private:
        enum Bits
        {
            TOP_LEFT_BIT = 0,
            LEFT_BIT = 1,
            BOTTOM_LEFT_BIT = 2,
            TOP_BIT = 3,
            BOTTOM_BIT = 4,
            TOP_RIGHT_BIT = 5,
            RIGHT_BIT = 6,
            BOTTOM_RIGHT_BIT = 7,
        };
        
        enum Neighbors
        {
            NONE = 0,
            TOP_LEFT = 1 << Bits::TOP_LEFT_BIT,
            LEFT = 1 <<  Bits::LEFT_BIT,
            BOTTOM_LEFT = 1 <<  Bits::BOTTOM_LEFT_BIT,
            TOP = 1 <<  Bits::TOP_BIT,
            BOTTOM = 1 <<  Bits::BOTTOM_BIT,
            TOP_RIGHT = 1 <<  Bits::TOP_RIGHT_BIT,
            RIGHT = 1 <<  Bits::RIGHT_BIT,
            BOTTOM_RIGHT = 1 <<  Bits::BOTTOM_RIGHT_BIT,
        };

        std::map<int, Tile> farmlandTiles;

    public:
        DirtTileBehavior();
        ~DirtTileBehavior();

        void behavior(const std::string &tilemapName, const glm::vec2 &actionCoords);
};