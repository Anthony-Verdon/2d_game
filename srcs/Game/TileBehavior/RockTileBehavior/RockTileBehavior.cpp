#include "Game/TileBehavior/RockTileBehavior/RockTileBehavior.hpp"
#include "Common/TileBehaviorType.hpp"
#include "Engine/2D/TilemapManager/TilemapManager.hpp"
#include "globals.hpp"
#include "Engine/2D/WorldPhysic/WorldPhysic.hpp"

RockTileBehavior::RockTileBehavior() : ATileBehavior()
{
    behaviorType = TileBehaviorType::ROCK;
}

RockTileBehavior::~RockTileBehavior()
{
}

void RockTileBehavior::behavior(const std::string &tilemapName, const ml::vec2 &actionCoords)
{
    TilemapManager::SuppressTile(tilemapName, actionCoords);
    TilemapManager::UpdateCollision(tilemapName, WorldPhysic::GetWorldId());
}