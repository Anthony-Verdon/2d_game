#pragma once

#include "Engine/AProgram/AProgram.hpp"
#include "Engine/Tilemap/Tilemap.hpp"
#include "Engine/Camera/Camera.hpp"
#include "Engine/Renderers/SpriteRenderer/SpriteRenderer.hpp"
#include "Editor/TileSelector/TileSelector.hpp"
#include <Box2D/Box2D.h>

class Editor: public AProgram
{
    private:
        Tilemap tilemap;
        Camera camera;
        bool ImGuiWindowHoweredOrFocused;
        TileSelector tileSelector;

        b2WorldId worldId;
        float timeStep;
        int subStepCount;
        b2DebugDraw debugDraw;
        void InitDebugDraw();

        void ProcessInput();
        void UpdateCamera();
        void UpdateTilemap();

        void Draw();
    public:
        Editor();
        ~Editor();

        void Run();

        void ScrollCallback(double xOffset, double yOffset);
};