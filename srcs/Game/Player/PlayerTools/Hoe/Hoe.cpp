#include "Game/Player/PlayerTools/Hoe/Hoe.hpp"
#include "Game/TileBehavior/TileBehaviorManager.hpp"
#include "Engine/TilemapManager/TilemapManager.hpp"
#include "Common/TileBehaviorType.hpp"

Hoe::Hoe()
{
    toolType = PlayerTool::HOE;
}

Hoe::~Hoe()
{
}

void Hoe::MainAction(const glm::vec2 &actionCoords)
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
