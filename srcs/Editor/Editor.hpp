#pragma once

#include "Engine/AGame/AGame.hpp"
#include "Engine/Tilemap/Tilemap.hpp"
#include "Engine/Camera/Camera.hpp"
#include "Engine/Renderers/SpriteRenderer/SpriteRenderer.hpp"
#include <Box2D/Box2D.h>

class Editor: public AGame
{
    private:
        Tilemap tilemap;
        Camera camera;
        Sprite actualSprite;

        b2WorldId worldId;
        float timeStep;
        int subStepCount;
        b2DebugDraw debugDraw;
        void InitDebugDraw();

        void CreateTileSelector();
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