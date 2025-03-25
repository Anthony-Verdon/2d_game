#pragma once

#include "Engine/AProgram/AProgram.hpp"
#include "Engine/Camera/Camera.hpp"
#include "Editor/ChainBuilder/ChainBuilder.hpp"
#include "Editor/ToolSelector/ToolSelector.hpp"
#include "Editor/TextureLoader/TextureLoader.hpp"
#include "Editor/FileExplorer/FileExplorer.hpp"
#include "Editor/TilemapManagerUI/TilemapManagerUI.hpp"
#include "Editor/AnimationCreator/AnimationCreator.hpp"
#include "Editor/TileBehaviorManager/TileBehaviorManager.hpp"
#include <box2d/box2d.h>
#include <vector>
#include <glm/glm.hpp>

class Editor: public AProgram
{
    private:
        Camera camera;
        bool ImGuiWindowHoweredOrFocused;
        ToolSelector toolSelector;
        FileExplorer fileExplorer;
        TilemapManagerUI tilemapManagerUI;
        AnimationCreator animationCreator;
        TextureLoader textureLoader;
        TileBehaviorManager tileBehaviorManager;
        
        b2WorldId worldId;
        float timeStep;
        int subStepCount;
        b2DebugDraw debugDraw;
        void InitDebugDraw();

        void ProcessInput();
        void UpdateCamera();
        void UpdateChain();
        void UpdateTilemap();

        void Draw();
    public:
        Editor();
        ~Editor();

        void Run();

        void ScrollCallback(double xOffset, double yOffset);
};