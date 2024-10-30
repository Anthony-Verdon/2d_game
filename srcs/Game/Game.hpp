#pragma once

#include <iostream>
#include "Engine/AGame/AGame.hpp"
#include "Game/Player/Player.hpp"
#include "Game/Barrel/Barrel.hpp"

class Game: public AGame
{
    private:
        Player player;
        Barrel barrel;
        void ProcessInput();

    public:
        Game();
        ~Game();

        void Run();
};