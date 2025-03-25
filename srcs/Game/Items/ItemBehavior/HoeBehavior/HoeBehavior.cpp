#include "Game/Items/ItemBehavior/HoeBehavior/HoeBehavior.hpp"
#include "Game/TileBehavior/TileBehaviorManager.hpp"
#include "Engine/2D/TilemapManager/TilemapManager.hpp"
#include "Common/TileBehaviorType.hpp"

HoeBehavior::HoeBehavior()
{
}

HoeBehavior::~HoeBehavior()
{
}

void HoeBehavior::MainAction(const glm::vec2 &actionCoords)
{
    std::vector<std::string> tilemaps = TilemapManager::GetTilemapOrder();
    for (int i = tilemaps.size() - 1; i >= 0; i--)
    {
        if (TilemapManager::TileExist(tilemaps[i], actionCoords))
        {
            Tile tile = TilemapManager::GetTile(tilemaps[i], actionCoords);
            
            for (size_t j = 0; j < tile.behaviors.size(); j++)
            {
                if (tile.behaviors[j] != TileBehaviorType::DIRT)
                    continue;

                TileBehaviorManager::behavior(tile.behaviors[j], tilemaps[i], actionCoords);
                break;
            }
            break;
        }
    }
}
