#include "Engine/SquareHitbox/SquareHitbox.hpp"

SquareHitbox::SquareHitbox()
{
    coords = glm::vec2(0, 0);
    size = glm::vec2(0, 0);
}

SquareHitbox::SquareHitbox(const glm::vec2 &coords, const glm::vec2 &size)
{
    this->coords = coords;
    this->size = size;
}

SquareHitbox::~SquareHitbox()
{
}

bool SquareHitbox::IsColliding(const SquareHitbox &instance) const
{
    bool collisionX = coords.x + size.x >= instance.GetX() && instance.GetX() + instance.GetWidth() >= coords.x;
    bool collisionY = coords.y + size.y >=  instance.GetY() && instance.GetY() + instance.GetHeight() >= coords.y;
    return collisionX && collisionY;
}

glm::vec2 SquareHitbox::GetCoords() const
{
    return (coords);
}

float SquareHitbox::GetX() const
{
    return (coords.x);
}

float SquareHitbox::GetY() const
{
    return (coords.y);
}

glm::vec2 SquareHitbox::GetSize() const
{
    return (size);
}

float SquareHitbox::GetWidth() const
{
    return (size.x);
}

float SquareHitbox::GetHeight() const
{
    return (size.y);
}

void SquareHitbox::Draw() const
{
    //todo
}