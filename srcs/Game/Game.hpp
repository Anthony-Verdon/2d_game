#pragma once

#include <iostream>
#include "Engine/AGame/AGame.hpp"
#include "Game/Player/Player.hpp"

class Game: public AGame
{
    private:
        Player player;
        SpriteRenderer barrel;
        void ProcessInput();

    public:
        Game();
        ~Game();

        void Run();
};