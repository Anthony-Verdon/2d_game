#pragma once

#include "Engine/AProgram/AProgram.hpp"
#include "Engine/2D/PhysicBody/PhysicBody.hpp"
#include "Engine/2D/TilemapManager/TilemapManager.hpp"
#include "Engine/2D/Camera/Camera.hpp"
#include <vector>
#include <glm/glm.hpp>
#include <box2d/box2d.h>
#include "Game/Player/Player.hpp"
#include "Game/Barrel/Barrel.hpp"
#include "Game/Skeletton/Skeletton.hpp"

class Game: public AProgram
{
    private:
        void ProcessInput();
        void Draw();

        void DebugRendering();

        void LoadChains();

        Player player;
        Barrel barrel;
        Skeletton skeletton;

        Camera camera;

    public:
        Game();
        ~Game();

        void Run();
        void ScrollCallback(double xOffset, double yOffset);
};