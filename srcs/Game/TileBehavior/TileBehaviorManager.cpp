#include "Game/TileBehavior/TileBehaviorManager.hpp"
#include "Game/TileBehavior/DirtTileBehavior/DirtTileBehavior.hpp"
#include "Common/TileBehaviorType.hpp"

std::map<TileBehaviorType, std::unique_ptr<ATileBehavior>> TileBehaviorManager::tileBehaviors;

void TileBehaviorManager::Init()
{
    tileBehaviors[TileBehaviorType::DIRT] = std::make_unique<DirtTileBehavior>();
    tileBehaviors[TileBehaviorType::ROCK] = std::make_unique<DirtTileBehavior>();// tmp
    tileBehaviors[TileBehaviorType::TREE] = std::make_unique<DirtTileBehavior>();//tmp
}

void TileBehaviorManager::behavior(TileBehaviorType type)
{
    tileBehaviors[type]->behavior();
}