#pragma once

#include "Engine/AGame/AGame.hpp"
#include "Engine/PhysicBody/PhysicBody.hpp"
#include <vector>
#include <glm/glm.hpp>
#include <Box2D/Box2D.h>
#include "Game/Player/Player.hpp"
#include "Game/Barrel/Barrel.hpp"

class Game: public AGame
{
    private:
        void ProcessInput();
        void Draw();

        void DebugRendering();

        // Box2D
        b2WorldId worldId;
        float timeStep;
        int subStepCount;

        Player player;
        Barrel barrel;

    public:
        Game();
        ~Game();

        void Run();
};