#include "Game/Items/ItemBehavior/PickaxeBehavior/PickaxeBehavior.hpp"
#include "Engine/TilemapManager/TilemapManager.hpp"
#include "Game/TileBehavior/TileBehaviorManager.hpp"
#include "Common/TileBehaviorType.hpp"

PickaxeBehavior::PickaxeBehavior()
{
}

PickaxeBehavior::~PickaxeBehavior()
{
}

void PickaxeBehavior::MainAction(const glm::vec2 &actionCoords)
{
    std::vector<std::string> tilemaps = TilemapManager::GetTilemapOrder();
    for (int i = tilemaps.size() - 1; i >= 0; i--)
    {
        if (TilemapManager::TileExist(tilemaps[i], actionCoords))
        {
            Tile tile = TilemapManager::GetTile(tilemaps[i], actionCoords);
            
            for (size_t j = 0; j < tile.behaviors.size(); j++)
            {
                if (tile.behaviors[j] != TileBehaviorType::ROCK)
                    continue;

                TileBehaviorManager::behavior(tile.behaviors[j], tilemaps[i], actionCoords);
                break;
            }
            break;
        }
    }
}