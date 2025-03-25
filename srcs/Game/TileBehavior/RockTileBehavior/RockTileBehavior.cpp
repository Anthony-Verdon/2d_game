#include "Game/TileBehavior/RockTileBehavior/RockTileBehavior.hpp"
#include "Common/TileBehaviorType.hpp"
#include "Engine/2D/TilemapManager/TilemapManager.hpp"
#include "globals.hpp"
#include "Game/WorldPhysic/WorldPhysic.hpp"

RockTileBehavior::RockTileBehavior(): ATileBehavior()
{
    behaviorType = TileBehaviorType::ROCK;
}

RockTileBehavior::~RockTileBehavior()
{
}

void RockTileBehavior::behavior(const std::string &tilemapName, const glm::vec2 &actionCoords)
{
    TilemapManager::SuppressTile(tilemapName, actionCoords);
    TilemapManager::UpdateCollision(tilemapName, WorldPhysic::GetWorldId());
}