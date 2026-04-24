#pragma once

#include <map>
#include <memory>
#include "Engine/2D/ATileBehavior/ATileBehavior.hpp"
#include <string>

class TileBehaviorManager
{
  private:
    static std::map<TileBehaviorType, std::unique_ptr<ATileBehavior>> tileBehaviors;

    TileBehaviorManager() = delete;
    ~TileBehaviorManager() = delete;

  public:
    static void Init();
    static void behavior(TileBehaviorType type, const std::string &tilemapName, const ml::vec2 &actionCoords);
};