#include "Engine/Transform/Transform.hpp"
#include "Engine/Time/Time.hpp"

Transform::Transform()
{
    position = glm::vec2(0, 0);
    rotation = 0;
}

Transform::Transform(const glm::vec2 &position, float rotation)
{
    this->position = position;
    this->rotation = rotation;
}

Transform::~Transform()
{

}

void Transform::Move(const glm::vec2 &amount)
{
    position += amount;
}

void Transform::Rotate(float amount)
{
    rotation += amount;
}

void Transform::AddForce(const glm::vec2 amount)
{
    force += amount;
}

void Transform::AddVelocity(const glm::vec2 amount)
{
    velocity += amount;
}


void Transform::Step()
{
    velocity += force * Time::getDeltaTime() * 10.0f;
    position += velocity * Time::getDeltaTime() * 10.0f;
    
    force = glm::vec2(0, 0);
}

void Transform::SetPosition(const glm::vec2 &position)
{
    this->position = position;
}

void Transform::SetRotation(float rotation)
{
    this->rotation = rotation;
}

glm::vec2 Transform::GetPosition() const
{
    return (position);
}

float Transform::GetRotation() const
{
    return (rotation);
}

glm::vec2 Transform::GetVelocity() const
{
    return (velocity);
}


