#include "Engine/CollisionChecker/CollisionChecker.hpp"

Collision CollisionChecker::CircleCollision(CircleRenderer* circleA, CircleRenderer* circleB)
{
    Collision collision;

    float distance = glm::length(circleA->GetPosition() - circleB->GetPosition());
    float bothRadius = circleA->GetRadius() + circleB->GetRadius();

    collision.doCollide = distance < bothRadius;
    collision.normal = glm::normalize(circleB->GetPosition() - circleA->GetPosition());
    collision.depth = bothRadius - distance;
   
    return collision;
}