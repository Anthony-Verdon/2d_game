#pragma once

#include <map>
#include <memory>
#include "Engine/ATileBehavior/ATileBehavior.hpp"
#include <string>
#include <glm/glm.hpp>

class TileBehaviorManager
{
    private:
        static std::map<TileBehaviorType, std::unique_ptr<ATileBehavior>> tileBehaviors;

        TileBehaviorManager() = delete;
        ~TileBehaviorManager() = delete;
    
    public:
        static void Init();
        static void behavior(TileBehaviorType type, const std::string &tilemapName, const glm::vec2 &actionCoords);
};