#include "Engine/SquareHitbox/SquareHitbox.hpp"
#include <glad/glad.h>

SquareHitbox::SquareHitbox(): GameObject()
{
    coords = glm::vec2(0, 0);
    size = glm::vec2(0, 0);
    AddComponent(std::make_unique<LineRenderer>());
}

SquareHitbox::SquareHitbox(const glm::vec2 &coords, const glm::vec2 &size): GameObject()
{
    this->coords = coords;
    this->size = size;
    AddComponent(std::make_unique<LineRenderer>());
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

void SquareHitbox::SetCoords(const glm::vec2 &coords)
{
    this->coords = coords;
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

void SquareHitbox::SetSize(const glm::vec2 &size)
{
    this->size = size;
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

void SquareHitbox::Draw()
{
    LineRenderer *lineRenderer = GetComponent<LineRenderer>();
    glLineWidth(2);
    lineRenderer->SetStart(coords);
    lineRenderer->SetEnd(coords + glm::vec2(size.x, 0));
    lineRenderer->Draw();

    lineRenderer->SetStart(coords);
    lineRenderer->SetEnd(coords + glm::vec2(0, size.y));
    lineRenderer->Draw();

    lineRenderer->SetStart(coords + glm::vec2(size.x, 0));
    lineRenderer->SetEnd(coords + size);
    lineRenderer->Draw();

    lineRenderer->SetStart(coords + glm::vec2(0, size.y));
    lineRenderer->SetEnd(coords + size);
    lineRenderer->Draw();
    glLineWidth(1);
}