#include "Game/Barrel/Barrel.hpp"
#include "Game/CategoriesFilter.hpp"
#include "Engine/Renderers/SpriteRenderer/SpriteRenderer.hpp"
#include "globals.hpp"

Barrel::Barrel()
{
}

Barrel::~Barrel()
{

}

void Barrel::Draw()
{
    SpriteRenderer::Draw(body.GetPosition(), size, body.GetAngle(), glm::vec3(1, 1, 1), "chest", glm::vec2(1, 1), glm::vec2(0, 0));
}

void Barrel::Init(b2WorldId worldId)
{
    glm::vec2 position = glm::vec2(WINDOW_WIDTH * 0.5, WINDOW_HEIGHT * 0.5);
    size = glm::vec2(SPRITE_SIZE, SPRITE_SIZE);
    b2Filter filter;
    filter.categoryBits = CategoriesFilter::Entities;
    filter.maskBits = CategoriesFilter::Wall;
    body = PhysicBody::Builder().SetPosition(position).SetSize(size).SetFilter(filter).Build(worldId);
}