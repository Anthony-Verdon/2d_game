#include "Engine/TilemapManager/TilemapManager.hpp"

TilemapManager::TilemapManager()
{
}

TilemapManager::~TilemapManager()
{
}

void TilemapManager::AddTile(const std::string &tilemapName, const glm::vec2 &position, const Tile &tile)
{
    auto it = tilemaps.find(tilemapName);
    if (it != tilemaps.end())
        it->second.AddTile(position, tile);
}

void TilemapManager::AddTile(const std::string &tilemapName, const glm::vec2 &position, const Sprite &sprite)
{
    auto it = tilemaps.find(tilemapName);
    if (it != tilemaps.end())
        it->second.AddTile(position, sprite);
}

void TilemapManager::SuppressTile(const std::string &tilemapName, const glm::vec2 &position)
{
    auto it = tilemaps.find(tilemapName);
    if (it != tilemaps.end())
        it->second.SuppressTile(position);
}

void TilemapManager::AddTilemap(const std::string &name, const Tilemap &tilemap)
{
    tilemaps[name] = tilemap;
    tilemapOrder.push_back(name);
}

void TilemapManager::Save()
{
    //@todo
}

void TilemapManager::Load()
{
    //@todo
}

void TilemapManager::Draw()
{
    for (size_t i = 0; i < tilemapOrder.size(); i++)
        tilemaps[tilemapOrder[i]].Draw();
}