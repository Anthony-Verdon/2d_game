#include "Game/PlayerTools/Pickaxe/Pickaxe.hpp"
#include "Game/WorldPhysic/WorldPhysic.hpp"
#include "Engine/TilemapManager/TilemapManager.hpp"

Pickaxe::Pickaxe()
{
    toolType = PlayerTool::PICKAXE;
}

Pickaxe::~Pickaxe()
{
}

void Pickaxe::MainAction(const glm::vec2 &actionCoords)
{
    std::vector<std::string> tilemaps = TilemapManager::GetTilemapOrder();
    for (int i = tilemaps.size() - 1; i >= 0; i--)
    {
        if (TilemapManager::SuppressTile(tilemaps[i], actionCoords))
        {
            TilemapManager::UpdateCollision(tilemaps[i], WorldPhysic::GetWorldId());
            break;
        }
    }
}