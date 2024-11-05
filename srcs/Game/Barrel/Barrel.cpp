#include "Game/Barrel/Barrel.hpp"
#include "globals.hpp"
#include "Engine/SpriteRenderer/SpriteRenderer.hpp"

Barrel::Barrel()
{
    AddComponent(std::make_unique<SpriteRenderer>("TileMapDungeon", 5.0f * glm::vec2(16, 16), glm::vec2(WINDOW_WIDTH / 2 - 5 * 8, WINDOW_HEIGHT / 2 - 5 * 8), 0, glm::vec3(1, 1, 1), 1, 1, false));
    GetComponent<SpriteRenderer>()->SetSprite(glm::vec2(12,11), glm::vec2(10,6));
}

Barrel::~Barrel()
{

}

void Barrel::Draw()
{
    GetComponent<SpriteRenderer>()->Draw();
}