#include "Game/Barrel/Barrel.hpp"
#include "globals.hpp"
#include "Engine/SpriteRenderer/SpriteRenderer.hpp"

Barrel::Barrel()
{
    coords = glm::vec2(WINDOW_WIDTH / 2 - 5 * 8, WINDOW_HEIGHT / 2 - 5 * 8);

    AddComponent(std::make_unique<SpriteRenderer>("TileMapDungeon", 5.0f * glm::vec2(16, 16), 0, glm::vec3(1, 1, 1)));
    GetComponent<SpriteRenderer>()->CalculateMesh(glm::vec2(12,11), glm::vec2(10,6));
    AddComponent(std::make_unique<SquareHitbox>(coords, 5.0f * glm::vec2(16, 16), glm::vec3(0, 0, 0)));
}

Barrel::~Barrel()
{

}

const SquareHitbox &Barrel::GetHitbox() const
{
    return (*(GetComponent<SquareHitbox>()));
}

void Barrel::Draw()
{
    GetComponent<SpriteRenderer>()->Draw(coords);
    GetComponent<SquareHitbox>()->Draw();
}