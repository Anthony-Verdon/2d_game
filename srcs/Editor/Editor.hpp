#pragma once

#include "Engine/AProgram/AProgram.hpp"
#include "Engine/Tilemap/Tilemap.hpp"
#include "Engine/Camera/Camera.hpp"
#include "Engine/Renderers/SpriteRenderer/SpriteRenderer.hpp"
#include "Editor/TileSelector/TileSelector.hpp"
#include "Editor/ChainBuilder/ChainBuilder.hpp"
#include "Editor/ToolSelector/ToolSelector.hpp"
#include <Box2D/Box2D.h>
#include <vector>
#include <glm/glm.hpp>

class Editor: public AProgram
{
    private:
        Tilemap tilemap;
        Camera camera;
        bool ImGuiWindowHoweredOrFocused;
        TileSelector tileSelector;
        ChainBuilder chainBuilder;
        ToolSelector toolSelector;
        
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