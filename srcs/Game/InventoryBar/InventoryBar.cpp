#include "Game/InventoryBar/InventoryBar.hpp"
#include "Engine/RessourceManager/RessourceManager.hpp"
#include "Engine/WindowManager/WindowManager.hpp"
#include "Engine/Renderers/SpriteRenderer/SpriteRenderer.hpp"
#include "globals.hpp"

InventoryBar::InventoryBar()
{
    RessourceManager::AddTexture("UI_Frames", "assets/UI/UI_Frames.png");
}

InventoryBar::~InventoryBar()
{
}

void InventoryBar::Draw(const Player &player)
{
    auto texture = RessourceManager::GetTexture("UI_Frames");
    size_t width = texture->getWidth();
    size_t height = texture->getHeight();
    glm::vec2 playerPos = player.GetPosition(); // @todo actually the middle of the screen, but we should be able to modify sprite renderer to draw at absolute coord
    glm::vec2 windowSize = WindowManager::GetWindowSize() / 2.0f;
    glm::vec2 topLeftCorner = -windowSize + playerPos;
    Sprite sprite;
    sprite.textureName = "UI_Frames";
    sprite.textureSize = glm::vec2(width, height) /  TILE_SIZE;
    for (int x = 0; x < sprite.textureSize.x; x++)
    {
        for (int y = 0; y < sprite.textureSize.y; y++)
        {
            sprite.spriteCoords = glm::vec2(x, y);
            SpriteRenderer::Draw(topLeftCorner + glm::vec2(x, y) * TILE_SIZE * 2.0f, glm::vec2(TILE_SIZE, TILE_SIZE) * 2.0f, 0, glm::vec3(1, 1, 1), sprite, false, false, 1);
        }
    }
}