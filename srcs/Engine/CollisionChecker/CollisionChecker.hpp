#pragma once 

#include "Engine/CircleRenderer/CircleRenderer.hpp"
#include "Engine/SquareRenderer/SquareRenderer.hpp"
#include <glm/glm.hpp>
#include <vector>
#include <map>

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

        static glm::vec2 ProjectVertices(const std::vector<glm::vec2> &vertices, const glm::vec2 &axis);
    public:
        static Collision CircleCollision(CircleRenderer* circleA, CircleRenderer* circleB);
        static Collision SquareCollision(SquareRenderer* squareA, SquareRenderer* squareB);

};