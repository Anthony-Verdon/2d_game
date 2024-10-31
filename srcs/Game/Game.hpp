#pragma once

#include <iostream>
#include "Engine/AGame/AGame.hpp"
#include "Game/Player/Player.hpp"
#include "Engine/CircleRenderer/CircleRenderer.hpp"
#include "Engine/SquareRenderer/SquareRenderer.hpp"
#include "Engine/LineRenderer/LineRenderer.hpp"
#include "Game/Barrel/Barrel.hpp"

class Game: public AGame
{
    private:
        Player player;
        Barrel barrel;
        CircleRenderer circle;
        SquareRenderer square;
        LineRenderer line;
        void ProcessInput();

    public:
        Game();
        ~Game();

        void Run();
};