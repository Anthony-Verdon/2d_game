#pragma once

#include <iostream>
#include "Engine/AGame/AGame.hpp"
#include "Game/Player/Player.hpp"
#include "Engine/ARenderer/ARenderer.hpp"
#include "Engine/ARenderer/ARenderer.hpp"
#include "Engine/LineRenderer/LineRenderer.hpp"
#include "Game/Barrel/Barrel.hpp"
#include <vector>

class Game: public AGame
{
    private:
        Player player;
        Barrel barrel;
        LineRenderer line;

        int nbShape;
        std::vector<std::unique_ptr<ARenderer>> shapes;
        
        void ProcessInput();
        void CheckCollisions();
        

    public:
        Game();
        ~Game();

        void Run();
};