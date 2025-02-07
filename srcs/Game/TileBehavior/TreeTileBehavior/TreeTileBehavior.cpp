#include "Game/TileBehavior/TreeTileBehavior/TreeTileBehavior.hpp"
#include "Common/TileBehaviorType.hpp"
#include "Engine/TilemapManager/TilemapManager.hpp"
#include "globals.hpp"
#include "Game/WorldPhysic/WorldPhysic.hpp"
#include "Game/LootManager/LootManager.hpp"
#include "Game/ItemDictionnary/ItemDictionnary.hpp"

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

        Loot loot;
        loot.sprite = ItemDictionnary::GetItem(Items::WOOD);
        size_t nbLoot = (rand() % 3) + 2;
        for (size_t i = 0; i < nbLoot; i++)
        {
            loot.position = actionCoords + glm::vec2(rand() % ((int)SPRITE_SIZE * 2) - SPRITE_SIZE, rand() % ((int)SPRITE_SIZE * 2) - SPRITE_SIZE);
            LootManager::AddLoot(loot);
        }
    }
}