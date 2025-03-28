#pragma once

#include "Editor/AEditorWindow/AEditorWindow.hpp"
#include <map>
#include "Common/TileBehaviorType.hpp"
#include <vector>
#include "Engine/2D/Tile/Tile.hpp"

class TileBehaviorManager: public AEditorWindow
{
    private:
        std::map<TileBehaviorType, std::vector<Tile>> tilesBehavior;
        
    public:
        TileBehaviorManager();
        ~TileBehaviorManager();

        void Load();
        
        void Draw();
};