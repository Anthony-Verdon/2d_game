#pragma once 

#include "Engine/CircleRenderer/CircleRenderer.hpp"
#include <glm/glm.hpp>

struct Collision
{
    bool doCollide;
    glm::vec2 normal;
    float depth;
};


class CollisionChecker
{
    private:
        CollisionChecker() = delete;
        ~CollisionChecker() = delete;

    public:
        static Collision CircleCollision(CircleRenderer* circleA, CircleRenderer* circleB);
};