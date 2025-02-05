#pragma once

#include <map>
#include <memory>
#include "Engine/ATileBehavior/ATileBehavior.hpp"

class TileBehaviorManager
{
    private:
        static std::map<TileBehaviorType, std::unique_ptr<ATileBehavior>> tileBehaviors;

        TileBehaviorManager() = delete;
        ~TileBehaviorManager() = delete;
    
    public:
        static void Init();
        static void behavior(TileBehaviorType type);
};