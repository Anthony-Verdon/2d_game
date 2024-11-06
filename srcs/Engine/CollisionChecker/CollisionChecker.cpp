#include "Engine/CollisionChecker/CollisionChecker.hpp"
#include <limits>
#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>

Collision CollisionChecker::CheckCollision(ARenderer *shapeA, ARenderer* shapeB)
{
    if (!IntersectAABB(GetAABB(shapeA), GetAABB(shapeB)))
        return (InitCollisionStruct(shapeA, shapeB));

    CircleRenderer* circleA = NULL;
    CircleRenderer* circleB = NULL;
    PolygonRenderer* polygonA = NULL;
    PolygonRenderer* polygonB = NULL;

    circleA = dynamic_cast<CircleRenderer*>(shapeA);
    if (!circleA)
        polygonA = dynamic_cast<PolygonRenderer*>(shapeA);

    circleB = dynamic_cast<CircleRenderer*>(shapeB);
    if (!circleB)
        polygonB = dynamic_cast<PolygonRenderer*>(shapeB);

    if (circleA && circleB)
        return (CircleCircleCollision(circleA, circleB));
    else if (polygonA && polygonB)
        return (PolygonPolygonCollision(polygonA, polygonB));
    else if (circleA && polygonB)
        return (CirclePolygonCollision(circleA, polygonB));
    else if (polygonA && circleB)
        return (CirclePolygonCollision(polygonA, circleB));
    else
        return (InitCollisionStruct(shapeA, shapeB));
}

AABB CollisionChecker::GetAABB(ARenderer* shape)
{
    CircleRenderer* circle = NULL;
    PolygonRenderer* polygon = NULL;

    AABB AABB_shape;
    AABB_shape.min.x = std::numeric_limits<float>::max();
    AABB_shape.min.y = std::numeric_limits<float>::max();
    AABB_shape.max.x = std::numeric_limits<float>::min();
    AABB_shape.max.y = std::numeric_limits<float>::min();
    circle = dynamic_cast<CircleRenderer*>(shape);
    if (circle)
    {
        AABB_shape.min.x = circle->GetPosition().x - circle->GetRadius();
        AABB_shape.min.y = circle->GetPosition().y - circle->GetRadius();
        AABB_shape.max.x = circle->GetPosition().x + circle->GetRadius();
        AABB_shape.max.y = circle->GetPosition().y + circle->GetRadius();
        return (AABB_shape);        
    }

    polygon = dynamic_cast<PolygonRenderer*>(shape);
    if (polygon)
    {
        std::vector<glm::vec2> vertices = polygon->CalculateVerticesPosition();
        for (unsigned int i = 0; i < vertices.size(); i++)
        {
            if (vertices[i].x < AABB_shape.min.x)
                AABB_shape.min.x = vertices[i].x;
            if (vertices[i].x > AABB_shape.max.x)
                AABB_shape.max.x = vertices[i].x;
            if (vertices[i].y < AABB_shape.min.y)
                AABB_shape.min.y = vertices[i].y;
            if (vertices[i].y > AABB_shape.max.y)
                AABB_shape.max.y = vertices[i].y;
        }
        return (AABB_shape);      
    }

    return (AABB_shape);        
}

bool CollisionChecker::IntersectAABB(AABB a, AABB b)
{
    return (a.max.x > b.min.x && b.max.x > b.min.x && a.max.y > b.min.y && b.max.y > b.min.y);
}

Collision CollisionChecker::CircleCircleCollision(CircleRenderer* circleA, CircleRenderer* circleB)
{
    Collision collision = InitCollisionStruct(circleA, circleB);

    glm::vec2 axis = circleB->GetPosition() - circleA->GetPosition();
    float distance = glm::length(axis);
    float bothRadius = circleA->GetRadius() + circleB->GetRadius();

    collision.doCollide = distance < bothRadius;
    if (collision.doCollide)
    {
        if (axis != glm::vec2(0, 0))
            collision.normal = glm::normalize(axis);
        else
            collision.normal = axis;
        collision.depth = bothRadius - distance;
        collision.contact1 = circleA->GetPosition() + collision.normal * circleA->GetRadius();
        collision.contactCount = 1;
    }
   
    return collision;
}

Collision CollisionChecker::PolygonPolygonCollision(PolygonRenderer* polygonA, PolygonRenderer* polygonB)
{
    Collision collision = InitCollisionStruct(polygonA, polygonB);
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

    Collision collision = InitCollisionStruct(circle, polygon);
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

Collision CollisionChecker::InitCollisionStruct(ARenderer *shapeA, ARenderer* shapeB)
{
    Collision collision;
    collision.shapeA = shapeA;
    collision.shapeB = shapeB;
    collision.doCollide = false;
    collision.normal = glm::vec2(0, 0);
    collision.depth = 0;
    collision.contact1 = glm::vec2(0, 0);
    collision.contact2 = glm::vec2(0, 0);
    collision.contactCount = 0;

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