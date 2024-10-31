#include "Engine/SquareHitbox/SquareHitbox.hpp"
#include <glad/glad.h>

SquareHitbox::SquareHitbox(): GameObject(), SquareData()
{
    AddComponent(std::make_unique<LineRenderer>());
}

SquareHitbox::SquareHitbox(const glm::vec2 &coords, const glm::vec2 &size, const glm::vec3 &color): GameObject(), SquareData(coords, size, color)
{
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

void SquareHitbox::Draw()
{
    LineRenderer *lineRenderer = GetComponent<LineRenderer>();
    lineRenderer->SetColor(color);
    glLineWidth(2);
    lineRenderer->SetStart(coords);
    lineRenderer->SetEnd(coords + glm::vec2(size.x, 0));
    lineRenderer->CalculateMesh();
    lineRenderer->Draw();

    lineRenderer->SetStart(coords);
    lineRenderer->SetEnd(coords + glm::vec2(0, size.y));
    lineRenderer->CalculateMesh();
    lineRenderer->Draw();

    lineRenderer->SetStart(coords + glm::vec2(size.x, 0));
    lineRenderer->SetEnd(coords + size);
    lineRenderer->CalculateMesh();
    lineRenderer->Draw();

    lineRenderer->SetStart(coords + glm::vec2(0, size.y));
    lineRenderer->SetEnd(coords + size);
    lineRenderer->CalculateMesh();
    lineRenderer->Draw();
    glLineWidth(1);
}