#pragma once 

#include "Engine/CircleRenderer/CircleRenderer.hpp"
#include "Engine/PolygonRenderer/PolygonRenderer.hpp"
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
        static glm::vec2 ProjectCircle(CircleRenderer* circle, const glm::vec2 &axis);
        static glm::vec2 findClosestVertex(CircleRenderer* circle, const std::vector<glm::vec2> &vertices);
    public:
        static Collision CircleCircleCollision(CircleRenderer* circleA, CircleRenderer* circleB);
        static Collision PolygonPolygonCollision(PolygonRenderer* polygonA, PolygonRenderer* polygonB);
        static Collision CirclePolygonCollision(CircleRenderer* circle, PolygonRenderer* polygon);
        static Collision CirclePolygonCollision(PolygonRenderer* polygon, CircleRenderer* circle);

};