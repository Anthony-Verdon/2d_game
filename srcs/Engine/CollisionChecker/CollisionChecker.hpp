#pragma once 

#include "Engine/CircleBody/CircleBody.hpp"
#include "Engine/PolygonBody/PolygonBody.hpp"
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
        static Collision CircleCircleCollision(CircleBody* circleA, CircleBody* circleB);
        static Collision PolygonPolygonCollision(PolygonBody* polygonA, PolygonBody* polygonB);
        static Collision CirclePolygonCollision(CircleBody* circle, PolygonBody* polygon);
        static Collision CirclePolygonCollision(PolygonBody* polygon, CircleBody* circle);

        static Collision InitCollisionStruct(ARenderer *shapeA, ARenderer *shapeB);
        static AABB GetAABB(CircleBody *shape);
        static AABB GetAABB(PolygonBody *shape);
        static Boundaries ProjectVertices(const std::vector<glm::vec2> &vertices, const glm::vec2 &axis);
        static Boundaries ProjectCircle(CircleBody* circle, const glm::vec2 &axis);
        static glm::vec2 findClosestVertex(CircleBody* circle, const std::vector<glm::vec2> &vertices);
    public:
        static Collision CheckCollision(ARenderer *shapeA, ARenderer *shapeB);

};