#pragma once

#include <iostream>
#include "Engine/AGame/AGame.hpp"
#include "Game/Player/Player.hpp"
#include "Engine/ARenderer/ARenderer.hpp"
#include "Engine/CollisionChecker/CollisionChecker.hpp"
#include "Game/Barrel/Barrel.hpp"
#include <vector>

class Game: public AGame
{
    private:
        Player player;
        Barrel barrel;

        std::vector<std::unique_ptr<ARenderer>> shapes;
        std::vector<Collision> collisions;        
        void ProcessInput();
        void CheckCollisions();
        

    public:
        Game();
        ~Game();

        void Run();
};