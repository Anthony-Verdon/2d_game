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

    glm::vec2 backgroundSize = glm::vec2(5, 5);
    DrawInventorySlotBackground(topLeftCorner, backgroundSize);
    DrawMultipleSlots(topLeftCorner, backgroundSize, glm::vec2(2, 2));
}

void InventoryBar::DrawInventorySlotBackground(const glm::vec2 &position, const glm::vec2 &size)
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

void InventoryBar::DrawMultipleSlots(const glm::vec2 &position, const glm::vec2 &backgroundSize, const glm::vec2 &nbSlot)
{
    int edge = 2;
    glm::vec2 nbGap;
    nbGap.x = edge + nbSlot.x - 1;
    nbGap.y = edge + nbSlot.y - 1;
    glm::vec2 gapSize;
    gapSize.x = ((backgroundSize.x - edge) * SLOT_SIZE - nbSlot.x * SLOT_SIZE) / nbGap.x;
    gapSize.y = ((backgroundSize.y - edge) * SLOT_SIZE - nbSlot.y * SLOT_SIZE) / nbGap.y;
    for (int x = 0; x < nbSlot.x; x++)
    {
        for (int y = 0; y < nbSlot.y; y++)
        {
            DrawInventorySlot(position + glm::vec2(x, y) * SLOT_SIZE + glm::vec2(x + 1, y + 1) * gapSize);
        }
    }
}

void InventoryBar::DrawInventorySlot(const glm::vec2 &position)
{
    auto texture = RessourceManager::GetTexture("UI_Frames");
    size_t width = texture->getWidth();
    size_t height = texture->getHeight();
    Sprite sprite;
    sprite.textureName = "UI_Frames";
    sprite.textureSize = glm::vec2(width, height) /  TILE_SIZE;

    for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            sprite.spriteCoords = glm::vec2(3, 0) + glm::vec2(x, y);
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