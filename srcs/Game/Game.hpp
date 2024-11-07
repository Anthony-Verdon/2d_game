#pragma once

#include "Engine/AGame/AGame.hpp"
#include <vector>
#include <glm/glm.hpp>

class Game: public AGame
{
    private:
        std::vector<glm::vec2> positions;
        
        void ProcessInput();
        void Draw();

        void DebugRendering();

    public:
        Game();
        ~Game();

        void Run();
};