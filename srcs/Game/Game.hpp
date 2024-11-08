#pragma once

#include "Engine/AGame/AGame.hpp"
#include <vector>
#include <glm/glm.hpp>
#include <Box2D/Box2D.h>

class Game: public AGame
{
    private:
        void ProcessInput();
        void Draw();

        void DebugRendering();

        // Box2D
        b2WorldId worldId;
        b2BodyId groundId;
        std::vector<b2BodyId> boxes;
        float timeStep;
        int subStepCount;

    public:
        Game();
        ~Game();

        void Run();
};