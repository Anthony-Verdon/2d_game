#include "Engine/TileDictionnary/TileDictionnary.hpp"

std::vector<Tile> TileDictionnary::tiles;

void TileDictionnary::AddTile(const Tile &tile)
{
    auto it = std::find(tiles.begin(), tiles.end(), tile);
    if (it == tiles.end())
        tiles.push_back(tile);
}

Tile TileDictionnary::GetTile(size_t index)
{
    if (index >= tiles.size())
        return Tile::none;
    return (tiles[index]);
}

size_t TileDictionnary::GetTileIndex(const Tile &tile)
{
    return (std::distance(tiles.begin(), std::find(tiles.begin(), tiles.end(), tile)));
}

size_t TileDictionnary::GetDictionnarySize()
{
    return (tiles.size());
}