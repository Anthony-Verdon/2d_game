#include "Engine/CollisionChecker/CollisionChecker.hpp"
#include <limits>
#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>

Collision CollisionChecker::CircleCollision(CircleRenderer* circleA, CircleRenderer* circleB)
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

Collision CollisionChecker::SquareCollision(SquareRenderer* squareA, SquareRenderer* squareB)
{
    /* temporary region, it calculates where the vertice of each square is */    
    std::vector<glm::vec2> vertices;
    vertices.push_back(glm::vec2(0,0));
    vertices.push_back(glm::vec2(1,0));
    vertices.push_back(glm::vec2(1,1));
    vertices.push_back(glm::vec2(0,1));

    glm::mat4 modelA = glm::mat4(1.0f);
    
    modelA = glm::translate(modelA, glm::vec3(squareA->GetPosition(), 0.0f));  
    
    modelA = glm::translate(modelA, glm::vec3(0.5f * squareA->GetWidth(), 0.5f * squareA->GetHeight(), 0.0f)); 
    modelA = glm::rotate(modelA, glm::radians(squareA->GetRotation()), glm::vec3(0.0f, 0.0f, 1.0f)); 
    modelA = glm::translate(modelA, glm::vec3(-0.5f * squareA->GetWidth(), -0.5f * squareA->GetHeight(), 0.0f));
    modelA = glm::scale(modelA, glm::vec3(squareA->GetSize(), 1.0f)); 

    glm::mat4 modelB = glm::mat4(1.0f);
    modelB = glm::translate(modelB, glm::vec3(squareB->GetPosition(), 0.0f));  
    modelB = glm::translate(modelB, glm::vec3(0.5f * squareB->GetWidth(), 0.5f * squareB->GetHeight(), 0.0f)); 
    modelB = glm::rotate(modelB, glm::radians(squareB->GetRotation()), glm::vec3(0.0f, 0.0f, 1.0f)); 
    modelB = glm::translate(modelB, glm::vec3(-0.5f * squareB->GetWidth(), -0.5f * squareB->GetHeight(), 0.0f)); 
    modelB = glm::scale(modelB, glm::vec3(squareB->GetSize(), 1.0f)); 

    std::vector<glm::vec2> verticesA;
    std::vector<glm::vec2> verticesB;
    for (int i = 0; i < 4; i++)
    {
        glm::vec4 tmpA = glm::vec4(vertices[i], 0, 1);
        tmpA = modelA * tmpA;
        verticesA.push_back(glm::vec2(tmpA.x, tmpA.y));

        glm::vec4 tmpB = glm::vec4(vertices[i], 0, 1);
        tmpB =  modelB * tmpB;
        verticesB.push_back(glm::vec2(tmpB.x, tmpB.y));
    }
    /* end temporary region */

    Collision collision;
    collision.doCollide = false;
    collision.normal = glm::vec2(0, 0);
    collision.depth = std::numeric_limits<float>::max();

    vertices = verticesA;
    for (int j = 0; j < 2; j++)
    {
        for (int i = 0; i < 4; i++)
        {
            glm::vec2 va = vertices[i];
            glm::vec2 vb = vertices[(i  + 1) % 4];
        
            glm::vec2 edge = vb - va;
            glm::vec2 axis = glm::vec2(-edge.y, edge.x);

            glm::vec2 minMaxA = ProjectVertices(verticesA, axis);
            float minA = minMaxA.x;
            float maxA = minMaxA.y;
            glm::vec2 minMaxB = ProjectVertices(verticesB, axis);
            float minB = minMaxB.x;
            float maxB = minMaxB.y;

            collision.doCollide = minA < maxB && minB < maxA;
            if (!collision.doCollide)
                return (collision);

            float axisDepth = std::min(maxB - minA, maxA - minB);
            if (axisDepth < collision.depth)
            {
                collision.depth = axisDepth;
                collision.normal = axis;
            }
        }
        vertices = verticesB;
    }

    collision.doCollide = true;
    collision.depth = collision.depth / glm::length(collision.normal);
    collision.normal = glm::normalize(collision.normal);

    glm::vec2 direction = squareB->GetPosition() - squareA->GetPosition();
    if (glm::dot(direction, collision.normal) < 0)
        collision.normal = -collision.normal;
    
    return (collision);
}

glm::vec2 CollisionChecker::ProjectVertices(const std::vector<glm::vec2> &vertices, const glm::vec2 &axis)
{
    float min = std::numeric_limits<float>::max();
    float max = std::numeric_limits<float>::min();
    for (int i = 0; i < 4; i++)
    {
        glm::vec2 vertex = vertices[i];
        float proj = glm::dot(vertex, axis);
        if (proj < min)
            min = proj;
        if (proj > max)
            max = proj;
    }

    return (glm::vec2(min, max));
}

Collision CollisionChecker::CircleSquareCollision(CircleRenderer* circle, SquareRenderer* square)
{
    /* temporary region, it calculates where the vertice of each square is */    
    std::vector<glm::vec2> vertices;
    vertices.push_back(glm::vec2(0,0));
    vertices.push_back(glm::vec2(1,0));
    vertices.push_back(glm::vec2(1,1));
    vertices.push_back(glm::vec2(0,1));

    glm::mat4 model = glm::mat4(1.0f);
    
    model = glm::translate(model, glm::vec3(square->GetPosition(), 0.0f));  
    
    model = glm::translate(model, glm::vec3(0.5f * square->GetWidth(), 0.5f * square->GetHeight(), 0.0f)); 
    model = glm::rotate(model, glm::radians(square->GetRotation()), glm::vec3(0.0f, 0.0f, 1.0f)); 
    model = glm::translate(model, glm::vec3(-0.5f * square->GetWidth(), -0.5f * square->GetHeight(), 0.0f));
    model = glm::scale(model, glm::vec3(square->GetSize(), 1.0f)); 

    for (int i = 0; i < 4; i++)
    {
        glm::vec4 tmp = glm::vec4(vertices[i], 0, 1);
        tmp = model * tmp;
        vertices[i].x = tmp.x;
        vertices[i].y = tmp.y;
    }
    /* end temporary region */
    Collision collision;
    collision.doCollide = false;
    collision.normal = glm::vec2(0, 0);
    collision.depth = std::numeric_limits<float>::max();

    for (int i = 0; i < 4; i++)
    {
        glm::vec2 va = vertices[i];
        glm::vec2 vb = vertices[(i  + 1) % 4];
    
        glm::vec2 edge = vb - va;
        glm::vec2 axis = glm::vec2(-edge.y, edge.x);

        glm::vec2 minMaxA = ProjectVertices(vertices, axis);
        float minA = minMaxA.x;
        float maxA = minMaxA.y;
        glm::vec2 minMaxB = ProjectCircle(circle, axis);
        float minB = minMaxB.x;
        float maxB = minMaxB.y;

        collision.doCollide = minA < maxB && minB < maxA;
        if (!collision.doCollide)
            return (collision);

        float axisDepth = std::min(maxB - minA, maxA - minB);
        if (axisDepth < collision.depth)
        {
            collision.depth = axisDepth;
            collision.normal = axis;
        }
    }

    glm::vec2 closestPoint = findClosestVertex(circle, vertices);
    glm::vec2 axis = closestPoint - circle->GetPosition();

    glm::vec2 minMaxA = ProjectVertices(vertices, axis);
    float minA = minMaxA.x;
    float maxA = minMaxA.y;
    glm::vec2 minMaxB = ProjectCircle(circle, axis);
    float minB = minMaxB.x;
    float maxB = minMaxB.y;
    collision.doCollide = minA < maxB && minB < maxA;
    if (!collision.doCollide)
        return (collision);

    float axisDepth = std::min(maxB - minA, maxA - minB);
    if (axisDepth < collision.depth)
    {
        collision.depth = axisDepth;
        collision.normal = axis;
    }

    collision.doCollide = true;
    collision.depth = collision.depth / glm::length(collision.normal);
    collision.normal = glm::normalize(collision.normal);

    glm::vec2 direction = square->GetPosition() - circle->GetPosition();
    if (glm::dot(direction, collision.normal) < 0)
        collision.normal = -collision.normal;

    return (collision);
}

Collision CollisionChecker::CircleSquareCollision(SquareRenderer* square, CircleRenderer* circle)
{
    Collision collision = CircleSquareCollision(circle, square);
    if (collision.doCollide)
    {
        collision.normal = -collision.normal;
    }

    return (collision);
}   

glm::vec2 CollisionChecker::ProjectCircle(CircleRenderer* circle, const glm::vec2 &axis)
{
    glm::vec2 direction = glm::normalize(axis);
    glm::vec2 directionAndRadius = direction * circle->GetRadius();

    glm::vec2 p1 = circle->GetPosition() + directionAndRadius;
    glm::vec2 p2 = circle->GetPosition() - directionAndRadius;

    float min = glm::dot(p1, axis);
    float max = glm::dot(p2, axis);
    if (min > max)
        std::swap(min, max);

    return (glm::vec2(min, max));
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