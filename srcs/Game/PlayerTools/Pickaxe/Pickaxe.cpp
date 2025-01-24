#include "Game/PlayerTools/Pickaxe/Pickaxe.hpp"
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
            break;
    }
}