#include "Game/TileBehavior/DirtTileBehavior/DirtTileBehavior.hpp"
#include "Common/TileBehaviorType.hpp"
#include "Engine/TilemapManager/TilemapManager.hpp"
#include "Engine/RessourceManager/RessourceManager.hpp"
#include "globals.hpp"

DirtTileBehavior::DirtTileBehavior(): ATileBehavior()
{
    behaviorType = TileBehaviorType::DIRT;

    RessourceManager::AddTexture("farmland", "assets/Tiles/FarmLand/FarmLand_Tile.png");
    farmlandTile.sprite.textureName = "farmland";
    farmlandTile.sprite.textureSize = glm::vec2(7, 8);
    farmlandTile.sprite.spriteCoords = glm::vec2(0, 0);
    farmlandTile.sprite.size = glm::vec2(SPRITE_SIZE, SPRITE_SIZE);
    farmlandTile.spriteOffset = glm::vec2(0, 0);
}

DirtTileBehavior::~DirtTileBehavior()
{
}

void DirtTileBehavior::behavior(const std::string &tilemapName, const glm::vec2 &actionCoords)
{
    TilemapManager::AddTile(tilemapName, actionCoords, farmlandTile);
}