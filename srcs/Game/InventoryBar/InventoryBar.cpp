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
    glm::vec2 playerPos = player.GetPosition(); // @todo actually the middle of the screen, but we should be able to modify sprite renderer to draw at absolute coord
    glm::vec2 windowSize = WindowManager::GetWindowSize() / 2.0f;
    glm::vec2 topLeftCorner = -windowSize + playerPos;

    DrawInventorySlot(topLeftCorner, glm::vec2(5, 3));
    
}

void InventoryBar::DrawInventorySlot(const glm::vec2 &position, const glm::vec2 &size)
{
    auto texture = RessourceManager::GetTexture("UI_Frames");
    size_t width = texture->getWidth();
    size_t height = texture->getHeight();
    Sprite sprite;
    sprite.textureName = "UI_Frames";
    sprite.textureSize = glm::vec2(width, height) /  TILE_SIZE;

    for (int x = 0; x < size.x; x++)
    {
        for (int y = 0; y < size.y; y++)
        {
            sprite.spriteCoords.x = DetermineSpriteCoord(x, size.x - 1);
            sprite.spriteCoords.y = DetermineSpriteCoord(y, size.y - 1);
            SpriteRenderer::Draw(position + glm::vec2(x, y) * SLOT_SIZE, glm::vec2(SLOT_SIZE, SLOT_SIZE), 0, glm::vec3(1, 1, 1), sprite, false, false, 1);
        }
    }
}

int InventoryBar::DetermineSpriteCoord(int coord, int size)
{
    if (coord == 0)
        return (0);
    else if (coord == size)
        return (2);
    else
        return (1);
}