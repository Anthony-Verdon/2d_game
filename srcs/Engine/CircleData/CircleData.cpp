#include "Engine/CircleData/CircleData.hpp"

CircleData::CircleData()
{
    radius = 100;
    center = glm::vec2(100, 100);
}

CircleData::CircleData(float radius, const glm::vec2 &center)
{
    this->radius = radius;
    this->center = center;
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

float CircleData::GetRadius() const
{
    return (radius);
}

glm::vec2 CircleData::GetCenter() const
{
    return (center);
}