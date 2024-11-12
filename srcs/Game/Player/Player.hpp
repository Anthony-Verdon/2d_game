#pragma once

#include "Engine/PhysicBody/PhysicBody.hpp"
#include <glm/glm.hpp>

class Player
{
    private:
        glm::vec2 size;
        PhysicBody body;

    public:
        Player();
        ~Player();

        void Draw();
        void Move(const glm::vec2 &amount);
        void Init(b2WorldId worldId);
};