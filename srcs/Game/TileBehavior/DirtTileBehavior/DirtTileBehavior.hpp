#pragma once

#include "Engine/ATileBehavior/ATileBehavior.hpp"
#include "Engine/Tile/Tile.hpp"

class DirtTileBehavior: public ATileBehavior
{
    private:
        Tile farmlandTile;

    public:
        DirtTileBehavior();
        ~DirtTileBehavior();

        void behavior(const std::string &tilemapName, const glm::vec2 &actionCoords);
};