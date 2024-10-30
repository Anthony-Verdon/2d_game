#include "Game/Barrel/Barrel.hpp"
#include "globals.hpp"

Barrel::Barrel()
{
    coords = glm::vec2(WINDOW_WIDTH / 2 - 5 * 8, WINDOW_HEIGHT / 2 - 5 * 8);
    spriteRenderer.SetTexture("TileMapDungeon");
    spriteRenderer.SetSize(5.0f * glm::vec2(16, 16));
    hitbox.SetCoords(coords);
    hitbox.SetSize(5.0f * glm::vec2(16, 16));
}

Barrel::~Barrel()
{

}

const SquareHitbox &Barrel::GetHitbox() const
{
    return (hitbox);
}

void Barrel::Draw()
{
    spriteRenderer.Draw(coords, glm::vec2(12,11), glm::vec2(10,6));
    hitbox.Draw();
}