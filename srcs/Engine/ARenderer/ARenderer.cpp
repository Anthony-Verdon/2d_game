#include "Engine/ARenderer/ARenderer.hpp"

ARenderer::ARenderer(RendererType type): GameObject()
{
    color = glm::vec3(0, 0, 0);
    this->type = type;
}

ARenderer::ARenderer(const glm::vec3 &color, const glm::vec2 &position, float rotation, float mass, float restitution, bool isStatic, RendererType type): GameObject(position, rotation, mass, restitution, isStatic)
{
    this->color = color;
    this->type = type;
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

RendererType ARenderer::GetType() const
{
    return (type);
}