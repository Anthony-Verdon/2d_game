#include "Engine/PhysicBody/PhysicBody.hpp"
#include "Engine/Time/Time.hpp"

PhysicBody::PhysicBody()
{
    position = glm::vec2(0, 0);
    rotation = 0;
}

PhysicBody::PhysicBody(const glm::vec2 &position, float rotation)
{
    this->position = position;
    this->rotation = rotation;
}

PhysicBody::~PhysicBody()
{

}

void PhysicBody::Move(const glm::vec2 &amount)
{
    position += amount;
}

void PhysicBody::Rotate(float amount)
{
    rotation += amount;
}

void PhysicBody::AddForce(const glm::vec2 amount)
{
    force += amount;
}

void PhysicBody::AddVelocity(const glm::vec2 amount)
{
    velocity += amount;
}


void PhysicBody::Step()
{
    velocity += force * Time::getDeltaTime() * 10.0f;
    position += velocity * Time::getDeltaTime() * 10.0f;
    
    force = glm::vec2(0, 0);
}

void PhysicBody::SetPosition(const glm::vec2 &position)
{
    this->position = position;
}

void PhysicBody::SetRotation(float rotation)
{
    this->rotation = rotation;
}

glm::vec2 PhysicBody::GetPosition() const
{
    return (position);
}

float PhysicBody::GetRotation() const
{
    return (rotation);
}

glm::vec2 PhysicBody::GetVelocity() const
{
    return (velocity);
}


