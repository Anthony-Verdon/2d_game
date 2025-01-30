#include "Game/Player/PlayerTools/Hoe/Hoe.hpp"
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
            
            for (size_t i = 0; i < tile.behaviors.size(); i++)
            {
                if (tile.behaviors[i]->GetType() != TileBehavior::DIRT)
                    continue;

                tile.behaviors[i]->behavior();
                break;
            }
            break;
        }
    }
}
