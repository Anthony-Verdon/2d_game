#pragma once

#include "Engine/AProgram/AProgram.hpp"
#include "Engine/PhysicBody/PhysicBody.hpp"
#include "Engine/Tilemap/Tilemap.hpp"
#include "Engine/Camera/Camera.hpp"
#include <vector>
#include <glm/glm.hpp>
#include <Box2D/Box2D.h>
#include "Game/Player/Player.hpp"
#include "Game/Barrel/Barrel.hpp"
#include "Game/Skeletton/Skeletton.hpp"

class Game: public AProgram
{
    private:
        void ProcessInput();
        void Draw();

        void DebugRendering();

        // Box2D
        b2WorldId worldId;
        float timeStep;
        int subStepCount;
        b2DebugDraw debugDraw;
        void InitDebugDraw();

        Player player;
        Barrel barrel;
        Skeletton skeletton;

        Tilemap tilemap;
        Camera camera;


    public:
        Game();
        ~Game();

        void Run();
        void ScrollCallback(double xOffset, double yOffset);
};