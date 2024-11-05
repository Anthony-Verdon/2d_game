#include "Engine/CollisionChecker/CollisionChecker.hpp"
#include <limits>
#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>

Collision CollisionChecker::CircleCircleCollision(CircleRenderer* circleA, CircleRenderer* circleB)
{
    Collision collision;
    collision.doCollide = false;
    collision.normal = glm::vec2(0, 0);
    collision.depth = 0;

    float distance = glm::length(circleA->GetPosition() - circleB->GetPosition());
    float bothRadius = circleA->GetRadius() + circleB->GetRadius();

    collision.doCollide = distance < bothRadius;
    if (collision.doCollide)
    {
        if (circleB->GetPosition() != circleA->GetPosition())
            collision.normal = glm::normalize(circleB->GetPosition() - circleA->GetPosition());
        collision.depth = bothRadius - distance;
    }
   
    return collision;
}

Collision CollisionChecker::PolygonPolygonCollision(PolygonRenderer* polygonA, PolygonRenderer* polygonB)
{
    Collision collision;
    collision.doCollide = false;
    collision.normal = glm::vec2(0, 0);
    collision.depth = std::numeric_limits<float>::max();

    std::vector<glm::vec2> verticesA = polygonA->CalculateVerticesPosition();
    std::vector<glm::vec2> verticesB = polygonB->CalculateVerticesPosition();
    std::vector<glm::vec2> vertices = verticesA;
    for (int j = 0; j < 2; j++)
    {
        for (unsigned int i = 0; i < vertices.size(); i++)
        {
            glm::vec2 va = vertices[i];
            glm::vec2 vb = vertices[(i  + 1) % vertices.size()];

            glm::vec2 edge = va - vb;
            glm::vec2 axis = glm::vec2(-edge.y, edge.x);

            Boundaries boundariesA = ProjectVertices(verticesA, axis);
            Boundaries boundariesB = ProjectVertices(verticesB, axis);
            collision.doCollide = boundariesA.min < boundariesB.max && boundariesB.min < boundariesA.max;
            if (!collision.doCollide)
                return (collision);

            float axisDepth = std::min(boundariesB.max - boundariesA.min, boundariesA.max -  boundariesB.min);
            if (axisDepth < collision.depth)
            {
                collision.depth = axisDepth;
                collision.normal = axis;
            }
        }

        vertices = polygonB->CalculateVerticesPosition();
    }

    collision.doCollide = true;
    collision.depth = collision.depth / glm::length(collision.normal);
    collision.normal = glm::normalize(collision.normal);

    glm::vec2 direction = polygonB->GetPosition() - polygonA->GetPosition();
    if (glm::dot(direction, collision.normal) < 0)
        collision.normal = -collision.normal;
    
    return (collision);
}

Collision CollisionChecker::CirclePolygonCollision(CircleRenderer* circle, PolygonRenderer* polygon)
{
    std::vector<glm::vec2> vertices = polygon->CalculateVerticesPosition();

    Collision collision;
    collision.doCollide = false;
    collision.normal = glm::vec2(0, 0);
    collision.depth = std::numeric_limits<float>::max();

    for (unsigned int i = 0; i < vertices.size(); i++)
    {
        glm::vec2 va = vertices[i];
        glm::vec2 vb = vertices[(i  + 1) % vertices.size()];
    
        glm::vec2 edge = va - vb;
        glm::vec2 axis = glm::vec2(-edge.y, edge.x);

        Boundaries boundariesA = ProjectVertices(vertices, axis);
        Boundaries boundariesB = ProjectCircle(circle, axis);
        collision.doCollide = boundariesA.min < boundariesB.max && boundariesB.min < boundariesA.max;
        if (!collision.doCollide)
            return (collision);

        float axisDepth = std::min(boundariesB.max - boundariesA.min, boundariesA.max -  boundariesB.min);
        if (axisDepth < collision.depth)
        {
            collision.depth = axisDepth;
            collision.normal = axis;
        }
    }

    glm::vec2 closestPoint = findClosestVertex(circle, vertices);
    glm::vec2 axis = closestPoint - circle->GetPosition();

    Boundaries boundariesA = ProjectVertices(vertices, axis);
    Boundaries boundariesB = ProjectCircle(circle, axis);
    collision.doCollide = boundariesA.min < boundariesB.max && boundariesB.min < boundariesA.max;
    if (!collision.doCollide)
        return (collision);

    float axisDepth = std::min(boundariesB.max - boundariesA.min, boundariesA.max -  boundariesB.min);
    if (axisDepth < collision.depth)
    {
        collision.depth = axisDepth;
        collision.normal = axis;
    }

    collision.doCollide = true;
    collision.depth = collision.depth / glm::length(collision.normal);
    collision.normal = glm::normalize(collision.normal);

    glm::vec2 direction = polygon->GetPosition() - circle->GetPosition();
    if (glm::dot(direction, collision.normal) < 0)
        collision.normal = -collision.normal;

    return (collision);
}

Collision CollisionChecker::CirclePolygonCollision(PolygonRenderer* polygon, CircleRenderer* circle)
{
    Collision collision = CirclePolygonCollision(circle, polygon);
    if (collision.doCollide)
        collision.normal = -collision.normal;

    return (collision);
}   

Boundaries CollisionChecker::ProjectVertices(const std::vector<glm::vec2> &vertices, const glm::vec2 &axis)
{
    Boundaries boundaries;
    boundaries.min = std::numeric_limits<float>::max();
    boundaries.max = std::numeric_limits<float>::min();
    for (unsigned int i = 0; i < vertices.size(); i++)
    {
        float proj = glm::dot(vertices[i], axis);
        if (proj < boundaries.min)
            boundaries.min = proj;
        if (proj > boundaries.max)
            boundaries.max = proj;
    }

    return (boundaries);
}

Boundaries CollisionChecker::ProjectCircle(CircleRenderer* circle, const glm::vec2 &axis)
{
    glm::vec2 directionAndRadius = glm::normalize(axis) * circle->GetRadius();

    Boundaries boundaries;
    boundaries.min = glm::dot(circle->GetPosition() + directionAndRadius, axis);
    boundaries.max = glm::dot(circle->GetPosition() - directionAndRadius, axis);
    if (boundaries.min > boundaries.max)
        std::swap(boundaries.min, boundaries.max);

    return (boundaries);
}

glm::vec2 CollisionChecker::findClosestVertex(CircleRenderer* circle, const std::vector<glm::vec2> &vertices)
{
    int index = -1;
    float minDistance = std::numeric_limits<float>::max();

    for (unsigned int i = 0; i < vertices.size(); i++)
    {
        float distance = glm::distance(vertices[i], circle->GetPosition());
        if (distance < minDistance)
        {
            minDistance = distance;
            index = i;
        }
    }

    return (vertices[index]);
}