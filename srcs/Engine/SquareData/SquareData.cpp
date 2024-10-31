#include "Engine/SquareData/SquareData.hpp"

SquareData::SquareData()
{
    coords = glm::vec2(0, 0);
    size = glm::vec2(0, 0);
    color = glm::vec3(0, 0, 0);
}

SquareData::SquareData(const glm::vec2 &coords, const glm::vec2 &size, const glm::vec3 &color)
{
    this->coords = coords;
    this->size = size;
    this->color = color;
}

SquareData::~SquareData()
{

}

void SquareData::SetCoords(const glm::vec2 &coords)
{
    this->coords = coords;
}

glm::vec2 SquareData::GetCoords() const
{
    return (coords);
}

float SquareData::GetX() const
{
    return (coords.x);
}

float SquareData::GetY() const
{
    return (coords.y);
}

void SquareData::SetSize(const glm::vec2 &size)
{
    this->size = size;
}

glm::vec2 SquareData::GetSize() const
{
    return (size);
}

float SquareData::GetWidth() const
{
    return (size.x);
}

float SquareData::GetHeight() const
{
    return (size.y);
}

void SquareData::SetColor(const glm::vec3 &color)
{
    this->color = color;
}

glm::vec3 SquareData::GetColor() const
{
    return (color);
}