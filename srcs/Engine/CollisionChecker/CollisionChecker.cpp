#include "Engine/CollisionChecker/CollisionChecker.hpp"
#include <limits>
#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/norm.hpp>
Collision CollisionChecker::CheckCollision(ARenderer *shapeA, ARenderer* shapeB)
{
    AABB AABB_shapeA;
    AABB AABB_shapeB;

    CircleRenderer* circleA = NULL;
    CircleRenderer* circleB = NULL;
    PolygonRenderer* polygonA = NULL;
    PolygonRenderer* polygonB = NULL;

    if (shapeA->GetType() == RendererType::Circle)
    {
        circleA = dynamic_cast<CircleRenderer*>(shapeA);
        AABB_shapeA = GetAABB(circleA);
    }
    else if (shapeA->GetType() == RendererType::Polygon)
    {
        polygonA = dynamic_cast<PolygonRenderer*>(shapeA);
        AABB_shapeA = GetAABB(polygonA);
    }

    if (shapeB->GetType() == RendererType::Circle)
    {
        circleB = dynamic_cast<CircleRenderer*>(shapeB);
        AABB_shapeB = GetAABB(circleB);
    }
    else if (shapeB->GetType() == RendererType::Polygon)
    {
        polygonB = dynamic_cast<PolygonRenderer*>(shapeB);
        AABB_shapeB = GetAABB(polygonB);
    }

    if (!IntersectAABB(AABB_shapeA, AABB_shapeB))
        return (InitCollisionStruct(shapeA, shapeB));

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

AABB CollisionChecker::GetAABB(CircleRenderer* circle)
{
    AABB AABB_shape;

    AABB_shape.min.x = std::numeric_limits<float>::max();
    AABB_shape.min.y = std::numeric_limits<float>::max();
    AABB_shape.max.x = std::numeric_limits<float>::min();
    AABB_shape.max.y = std::numeric_limits<float>::min();
    
    AABB_shape.min.x = circle->GetPosition().x - circle->GetRadius();
    AABB_shape.min.y = circle->GetPosition().y - circle->GetRadius();
    AABB_shape.max.x = circle->GetPosition().x + circle->GetRadius();
    AABB_shape.max.y = circle->GetPosition().y + circle->GetRadius();
    return (AABB_shape);        
}

AABB CollisionChecker::GetAABB(PolygonRenderer* polygon)
{
    AABB AABB_shape;

    AABB_shape.min.x = std::numeric_limits<float>::max();
    AABB_shape.min.y = std::numeric_limits<float>::max();
    AABB_shape.max.x = std::numeric_limits<float>::min();
    AABB_shape.max.y = std::numeric_limits<float>::min();
    
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
    
    // collision point 
    float minDistanceSquared = std::numeric_limits<float>::max();
    for (unsigned int i = 0; i < verticesA.size(); i++)
    {
        glm::vec2 vc = verticesA[i];
        for (unsigned int j = 0; j < verticesB.size(); j++)
        {
            // point segment distance
            glm::vec2 va = verticesB[j];
            glm::vec2 vb = verticesB[(j  + 1) % verticesB.size()];

            glm::vec2 ab = vb - va;
            glm::vec2 ac = vc - va;
            float proj = glm::dot(ac, ab);
            float lengthSquared = glm::length2(ab); // return glm::length * glm::length
            float d = proj / lengthSquared;

            glm::vec2 contact;
            if (d <= 0)
            {
                contact = va;
            }
            else if (d >= 1)
            {
                contact = vb;
            }
            else
            {
                contact = va + ab * d;
            }

            float distanceSquared = glm::distance2(vc, contact); // return glm::distance * glm::distance
            // end point segment distance

            if (std::abs(minDistanceSquared - distanceSquared) <= 0.005f) // to avoid problem of comparaison == or != with float values
            {
                if (std::abs(contact.x - collision.contact1.x) > 0.005f || std::abs(contact.y - collision.contact1.y) > 0.005f) // to avoid problem of comparaison == or != with float values 
                {
                    collision.contact2 = contact;
                    collision.contactCount = 2;
                }
            }
            else if (distanceSquared < minDistanceSquared)
            {
                minDistanceSquared = distanceSquared;
                collision.contact1 = contact;
                collision.contactCount = 1;
            }
        }
    }
    // second part
    for (unsigned int i = 0; i < verticesB.size(); i++)
    {
        glm::vec2 vc = verticesB[i];
        for (unsigned int j = 0; j < verticesA.size(); j++)
        {
            // point segment distance
            glm::vec2 va = verticesA[j];
            glm::vec2 vb = verticesA[(j  + 1) % verticesA.size()];

            glm::vec2 ab = vb - va;
            glm::vec2 ac = vc - va;
            float proj = glm::dot(ac, ab);
            float lengthSquared = glm::length2(ab); // return glm::length * glm::length
            float d = proj / lengthSquared;

            glm::vec2 contact;
            if (d <= 0)
            {
                contact = va;
            }
            else if (d >= 1)
            {
                contact = vb;
            }
            else
            {
                contact = va + ab * d;
            }

            float distanceSquared = glm::distance2(vc, contact); // return glm::distance * glm::distance
            // end point segment distance
            
            if (std::abs(minDistanceSquared - distanceSquared) <= 0.005f) // to avoid problem of comparaison == or != with float values
            {
                if (std::abs(contact.x - collision.contact1.x) > 0.005f || std::abs(contact.y - collision.contact1.y) > 0.005f) // to avoid problem of comparaison == or != with float values
                {
                    collision.contact2 = contact;
                    collision.contactCount = 2;
                }
            }
            else if (distanceSquared < minDistanceSquared)
            {
                minDistanceSquared = distanceSquared;
                collision.contact1 = contact;
                collision.contactCount = 1;
            }
        }
    }
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

    // collision point 
    float minDistanceSquared = std::numeric_limits<float>::max();
    for (unsigned int i = 0; i < vertices.size(); i++)
    {
        // point segment distance
        glm::vec2 va = vertices[i];
        glm::vec2 vb = vertices[(i  + 1) % vertices.size()];

        glm::vec2 ab = vb - va;
        glm::vec2 ac = circle->GetPosition() - va;
        float proj = glm::dot(ac, ab);
        float lengthSquared = glm::length2(ab); // return glm::length * glm::length
        float d = proj / lengthSquared;

        glm::vec2 contact;
        if (d <= 0)
        {
            contact = va;
        }
        else if (d >= 1)
        {
            contact = vb;
        }
        else
        {
            contact = va + ab * d;
        }

        float distanceSquared = glm::distance2(circle->GetPosition(), contact); // return glm::distance * glm::distance
        // end point segment distance

        if (distanceSquared < minDistanceSquared)
        {
            minDistanceSquared = distanceSquared;
            collision.contact1 = contact;
        }
        
    }
    collision.contactCount = 1;
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