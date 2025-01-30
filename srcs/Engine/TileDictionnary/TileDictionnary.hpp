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
        
        static Tile GetTile(size_t index);
        static size_t GetTileIndex(const Tile &tile);
        static size_t GetDictionnarySize();
};