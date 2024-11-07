#pragma once

#include "Engine/AGame/AGame.hpp"

class Game: public AGame
{
    private:
        void ProcessInput();

        void DebugRendering();
    public:
        Game();
        ~Game();

        void Run();
};