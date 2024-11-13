#include "Game/Barrel/Barrel.hpp"
#include "Game/Game.hpp"
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
    SpriteRenderer::Draw(body.GetPosition(), size, body.GetAngle(), glm::vec3(1, 1, 1), "TileMapDungeon", glm::vec2(12,11), glm::vec2(10, 6));
}

void Barrel::Init(b2WorldId worldId)
{
    glm::vec2 position = glm::vec2(WINDOW_WIDTH * 0.5, WINDOW_HEIGHT * 0.5);
    size = glm::vec2(SPRITE_SIZE, SPRITE_SIZE);
    body = PhysicBody::Builder().SetPosition(position).SetSize(size).Build(worldId);
}