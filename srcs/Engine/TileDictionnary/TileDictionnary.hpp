#pragma once

#include "Engine/Tile/Tile.hpp"
#include <vector>

class TileDictionnary
{
    private:
        std::vector<Tile> tiles;

    public:
        TileDictionnary();
        ~TileDictionnary();

        void AddTile(const Tile &tile);
        
        Tile GetTile(size_t index) const;
        size_t GetTileIndex(const Tile &tile) const;
        size_t GetDictionnarySize() const;

};