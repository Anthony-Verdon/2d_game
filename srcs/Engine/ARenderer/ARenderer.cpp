#include "Engine/ARenderer/ARenderer.hpp"
#include "Engine/Time/Time.hpp"

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

void ARenderer::AddForce(const glm::vec2 amount)
{
    force += amount;
}

#include "globals.hpp"
void ARenderer::Step()
{
    linearVelocity += force * Time::getDeltaTime() * 10.0f;
    position += linearVelocity * Time::getDeltaTime() * 10.0f;
    if (position.x > WINDOW_WIDTH)
        position.x = position.x - WINDOW_WIDTH;
    else if (position.x < 0)
        position.x = position.x + WINDOW_WIDTH;
    if (position.y > WINDOW_HEIGHT)
        position.y = position.y - WINDOW_HEIGHT;
    else if (position.y < 0)
        position.y = position.y + WINDOW_HEIGHT;
    force = glm::vec2(0, 0);
}