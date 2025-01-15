#include "Engine/Tilemap/Tilemap.hpp"
#include "Engine/Renderers/SpriteRenderer/SpriteRenderer.hpp"
#include "globals.hpp"

Tilemap::Tilemap()
{

}

Tilemap::~Tilemap()
{

}

void Tilemap::AddTile(const glm::vec2 &position, const Tile &tile)
{
    tiles[position] = tile;
}

void Tilemap::AddTile(const glm::vec2 &position, const Sprite &sprite)
{
    Tile tile;
    tile.sprite = sprite;
    AddTile(position, tile);
}

void Tilemap::SuppressTile(const glm::vec2 &position)
{
    auto it = tiles.find(position);
    if (it != tiles.end())
        tiles.erase(it);
}

void Tilemap::Draw()
{
    for (auto it = tiles.begin(); it != tiles.end(); it++)
        SpriteRenderer::Draw(it->first, glm::vec2(SPRITE_SIZE, SPRITE_SIZE), 0, glm::vec3(1, 1, 1), it->second.sprite, false, false, 1);
}

const std::map<glm::vec2, Tile, Vec2Comparator>& Tilemap::GetTiles() const
{
    return (tiles);
}
