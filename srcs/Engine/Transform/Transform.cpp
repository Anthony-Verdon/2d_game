#include "Engine/Transform/Transform.hpp"

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


