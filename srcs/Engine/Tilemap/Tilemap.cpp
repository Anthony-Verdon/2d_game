#include "Engine/Tilemap/Tilemap.hpp"
#include "Engine/Renderers/SpriteRenderer/SpriteRenderer.hpp"

Tilemap::Tilemap()
{

}

Tilemap::~Tilemap()
{

}

void Tilemap::AddTile(const Tile &tile)
{
    if (std::find(tiles.begin(), tiles.end(), tile) == tiles.end())
        tiles.push_back(tile);
}

void Tilemap::AddTile(const glm::vec2 &position, const glm::vec2 &size)
{
    Tile tile;
    tile.position = position;
    tile.size = size;
    AddTile(tile);
}

void Tilemap::Draw()
{
    for (unsigned int i = 0; i < tiles.size(); i++)
        SpriteRenderer::Draw(tiles[i].position, tiles[i].size, 0, glm::vec3(1, 1, 1), "TileMapDungeon", glm::vec2(12,11), glm::vec2(0, 0));
}