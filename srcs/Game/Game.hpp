#pragma once

#include <iostream>
#include "Engine/AGame/AGame.hpp"
#include "Game/Player/Player.hpp"
#include "Engine/CircleRenderer/CircleRenderer.hpp"
#include "Engine/SquareRenderer/SquareRenderer.hpp"
#include "Engine/LineRenderer/LineRenderer.hpp"
#include "Game/Barrel/Barrel.hpp"
#include <vector>

class Game: public AGame
{
    private:
        Player player;
        Barrel barrel;
        SquareRenderer square;
        LineRenderer line;

        std::vector<std::unique_ptr<CircleRenderer>> circles;
        void ProcessInput();
        void CheckCollisions();
        

    public:
        Game();
        ~Game();

        void Run();
};