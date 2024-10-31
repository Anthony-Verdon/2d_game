#include "Engine/CircleData/CircleData.hpp"

CircleData::CircleData()
{
    radius = 100;
    center = glm::vec2(100, 100);
    color = glm::vec3(0,0,0);
}

CircleData::CircleData(float radius, const glm::vec2 &center, const glm::vec3 &color)
{
    this->radius = radius;
    this->center = center;
    this->color = color;
}

CircleData::~CircleData()
{
}

void CircleData::SetRadius(float radius)
{
    this->radius = radius;
}

void CircleData::SetCenter(const glm::vec2 &center)
{
    this->center = center;
}

void CircleData::SetColor(const glm::vec3 &color)
{
    this->color = color;
}

float CircleData::GetRadius() const
{
    return (radius);
}

glm::vec2 CircleData::GetCenter() const
{
    return (center);
}

glm::vec3 CircleData::GetColor() const
{
    return (color);
}
