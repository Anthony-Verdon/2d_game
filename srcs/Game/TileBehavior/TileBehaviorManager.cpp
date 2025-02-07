#include "Game/TileBehavior/TileBehaviorManager.hpp"
#include "Game/TileBehavior/DirtTileBehavior/DirtTileBehavior.hpp"
#include "Game/TileBehavior/RockTileBehavior/RockTileBehavior.hpp"
#include "Game/TileBehavior/TreeTileBehavior/TreeTileBehavior.hpp"
#include "Common/TileBehaviorType.hpp"

std::map<TileBehaviorType, std::unique_ptr<ATileBehavior>> TileBehaviorManager::tileBehaviors;

void TileBehaviorManager::Init()
{
    tileBehaviors[TileBehaviorType::DIRT] = std::make_unique<DirtTileBehavior>();
    tileBehaviors[TileBehaviorType::ROCK] = std::make_unique<RockTileBehavior>();
    tileBehaviors[TileBehaviorType::TREE] = std::make_unique<TreeTileBehavior>();
}

void TileBehaviorManager::behavior(TileBehaviorType type, const std::string &tilemapName, const glm::vec2 &actionCoords)
{
    tileBehaviors[type]->behavior(tilemapName, actionCoords);
}