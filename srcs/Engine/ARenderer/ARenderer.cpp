#include "Engine/ARenderer/ARenderer.hpp"

ARenderer::ARenderer()
{
    color = glm::vec3(0, 0, 0);
}

ARenderer::ARenderer(const glm::vec3 &color)
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
