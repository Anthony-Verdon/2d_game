#pragma once

#include "Engine/PhysicBody/PhysicBody.hpp"
#include <glm/glm.hpp>

class Barrel
{
    private:
        glm::vec2 size;
        PhysicBody body;

    public:
        Barrel();
        ~Barrel();

        void Draw();
        void Init(b2WorldId worldId);
};