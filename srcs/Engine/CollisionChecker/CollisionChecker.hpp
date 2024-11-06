#pragma once 

#include "Engine/CircleRenderer/CircleRenderer.hpp"
#include "Engine/PolygonRenderer/PolygonRenderer.hpp"
#include <glm/glm.hpp>
#include <vector>
#include <map>

struct Boundaries
{
    float min;
    float max;
};

struct AABB
{
    glm::vec2 min;
    glm::vec2 max;
};

struct Collision
{
    ARenderer* shapeA;
    ARenderer* shapeB;
    bool doCollide;
    glm::vec2 normal;
    float depth;
    glm::vec2 contact1;
    glm::vec2 contact2;
    unsigned int contactCount;
};


class CollisionChecker
{
    private:
        CollisionChecker() = delete;
        ~CollisionChecker() = delete;

        static bool IntersectAABB(AABB a, AABB b);
        static Collision CircleCircleCollision(CircleRenderer* circleA, CircleRenderer* circleB);
        static Collision PolygonPolygonCollision(PolygonRenderer* polygonA, PolygonRenderer* polygonB);
        static Collision CirclePolygonCollision(CircleRenderer* circle, PolygonRenderer* polygon);
        static Collision CirclePolygonCollision(PolygonRenderer* polygon, CircleRenderer* circle);

        static Collision InitCollisionStruct(ARenderer *shapeA, ARenderer *shapeB);
        static AABB GetAABB(ARenderer *shape);
        static Boundaries ProjectVertices(const std::vector<glm::vec2> &vertices, const glm::vec2 &axis);
        static Boundaries ProjectCircle(CircleRenderer* circle, const glm::vec2 &axis);
        static glm::vec2 findClosestVertex(CircleRenderer* circle, const std::vector<glm::vec2> &vertices);
    public:
        static Collision CheckCollision(ARenderer *shapeA, ARenderer *shapeB);

};