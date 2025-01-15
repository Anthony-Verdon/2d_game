#include "Engine/TilemapManager/TilemapManager.hpp"

TilemapManager::TilemapManager()
{
}

TilemapManager::~TilemapManager()
{
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