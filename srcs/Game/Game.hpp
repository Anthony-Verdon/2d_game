#pragma once

#include <iostream>
#include "Engine/AGame/AGame.hpp"
#include "Game/Player/Player.hpp"
#include "Engine/CircleRenderer/CircleRenderer.hpp"
#include "Engine/PolygonRenderer/PolygonRenderer.hpp"
#include "Engine/LineRenderer/LineRenderer.hpp"
#include "Game/Barrel/Barrel.hpp"
#include <vector>

class Game: public AGame
{
    private:
        Player player;
        Barrel barrel;
        LineRenderer line;

        int nbCircle;
        std::vector<std::unique_ptr<CircleRenderer>> circles;
        int nbSquare;
        std::vector<std::unique_ptr<PolygonRenderer>> squares;
        
        void ProcessInput();
        void CheckCollisions();
        

    public:
        Game();
        ~Game();

        void Run();
};