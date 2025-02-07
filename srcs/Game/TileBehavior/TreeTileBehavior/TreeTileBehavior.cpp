#include "Game/TileBehavior/TreeTileBehavior/TreeTileBehavior.hpp"
#include "Common/TileBehaviorType.hpp"
#include "Engine/TilemapManager/TilemapManager.hpp"
#include "globals.hpp"
#include "Game/WorldPhysic/WorldPhysic.hpp"

TreeTileBehavior::TreeTileBehavior(): ATileBehavior()
{
    behaviorType = TileBehaviorType::TREE;
}

TreeTileBehavior::~TreeTileBehavior()
{
}

void TreeTileBehavior::behavior(const std::string &tilemapName, const glm::vec2 &actionCoords)
{
    Tile treeTile = TilemapManager::GetTile(tilemapName, actionCoords);
    if (treeTile.sprite.spriteCoords.x == 0)
    {
        TilemapManager::SuppressTile(tilemapName, actionCoords);
        TilemapManager::UpdateCollision(tilemapName, WorldPhysic::GetWorldId());
    }
    else
    {
        treeTile.sprite.spriteCoords.x = 0;
        TilemapManager::AddTile(tilemapName, actionCoords, treeTile);
    }
}