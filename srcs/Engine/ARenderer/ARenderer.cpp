#include "Engine/ARenderer/ARenderer.hpp"

ARenderer::ARenderer(): GameObject()
{
    color = glm::vec3(0, 0, 0);
}

ARenderer::ARenderer(const glm::vec3 &color, const glm::vec2 &position, float rotation): GameObject(position, rotation)
{
    this->color = color;
}

ARenderer::~ARenderer()
{

}

void ARenderer::SetColor(const glm::vec3 &color)
{
    this->color = color;
}

glm::vec3 ARenderer::GetColor() const
{
    return (color);
}
