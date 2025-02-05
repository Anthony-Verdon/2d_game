#pragma once

#include "Engine/Tile/Tile.hpp"
#include <vector>

class TileDictionnary
{
    private:
        static std::vector<Tile> tiles;

        TileDictionnary() = delete;
        ~TileDictionnary() = delete;

    public:

        static void AddTile(const Tile &tile);
        static void AddTileBehavior(size_t index, TileBehaviorType behavior);
         
        static Tile GetTile(size_t index);  
        static size_t GetTileIndex(const Tile &tile);
        static size_t GetDictionnarySize();
};