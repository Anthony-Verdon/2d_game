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
    tiles.insert(tile);
}

void Tilemap::AddTile(const glm::vec2 &position, const glm::vec2 &size, const PhysicBody& body)
{
    Tile tile;
    tile.position = position;
    tile.size = size;
    tile.body = body;
    AddTile(tile);
}

void Tilemap::SuppressTile(const glm::vec2 &position)
{
    for (auto it = tiles.begin(); it != tiles.end(); it++)
    {
        if (it->position == position)
        {
            tiles.erase(it);
            return;
        }
    }
}

void Tilemap::Draw()
{
    for (auto it = tiles.begin(); it != tiles.end(); it++)
    {   
        Sprite sprite;
        sprite.textureName = "grass";
        sprite.textureSize = glm::vec2(1, 1);
        sprite.spriteCoords = glm::vec2(0, 0);
        SpriteRenderer::Draw(it->position, it->size, 0, glm::vec3(1, 1, 1), sprite, false, false);
    }
}