#include "Engine/PhysicBody/PhysicBody.hpp"
#include "Engine/Time/Time.hpp"

PhysicBody::PhysicBody()
{
    position = glm::vec2(0, 0);
    rotation = 0;
    mass = 1;
    restitution = 1;
}

PhysicBody::PhysicBody(const glm::vec2 &position, float rotation, float mass, float restitution)
{
    this->position = position;
    this->rotation = rotation;
    this->mass = mass;
    this->restitution = restitution;
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

void PhysicBody::SetMass(float mass)
{
    this->mass = mass;
}

void PhysicBody::SetRestitution(float restitution)
{
    this->restitution = restitution;
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

float PhysicBody::GetMass() const
{
    return (mass);
}

float PhysicBody::GetRestitution() const
{
    return (restitution);
}

