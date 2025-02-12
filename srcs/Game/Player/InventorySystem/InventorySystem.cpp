#include "Game/Player/InventorySystem/InventorySystem.hpp"
#include "Game/Player/Player.hpp"
#include "Engine/RessourceManager/RessourceManager.hpp"
#include "Engine/WindowManager/WindowManager.hpp"
#include "Engine/Renderers/SpriteRenderer/SpriteRenderer.hpp"
#include "Engine/Renderers/LineRenderer/LineRenderer.hpp"
#include "globals.hpp"

InventorySystem::InventorySystem()
{
    RessourceManager::AddTexture("UI_Frames", "assets/UI/UI_Frames.png");
    RessourceManager::AddTexture("UI_Selectors", "assets/UI/UI_Selectors.png");
    
    slotSelected = glm::vec2(0, 0);
    open = false;
}

InventorySystem::~InventorySystem()
{
}

void InventorySystem::Draw(const Player &player)
{
    (void)player;

    if (open)
        DrawFullInventory();
    else
        DrawInventoryBar();
}

void InventorySystem::DrawInventoryBar()
{
    glm::vec2 backgroundSize = glm::vec2(12, 3);
    glm::vec2 position = glm::vec2(WindowManager::GetWindowWidth() / 2.0f - backgroundSize.x / 2.0f * SLOT_SIZE, WindowManager::GetWindowHeight() - SLOT_SIZE * 2.0f);
    glm::vec2 nbSlot = glm::vec2(6, 1);
    DrawInventorySlotBackground(position, backgroundSize);
    DrawMultipleSlots(position, backgroundSize, nbSlot, true);
}

void InventorySystem::DrawFullInventory()
{
    glm::vec2 backgroundSize = glm::vec2(12, 3);
    glm::vec2 position = WindowManager::GetWindowSize() / 2.0f - backgroundSize / 2.0f * SLOT_SIZE - glm::vec2(0, 2 * SLOT_SIZE);
    glm::vec2 nbSlot = glm::vec2(6, 1);
    DrawInventorySlotBackground(position, backgroundSize);
    DrawMultipleSlots(position, backgroundSize, nbSlot, true);

    backgroundSize = glm::vec2(12, 7);
    position = position + glm::vec2(0, 2 * SLOT_SIZE);
    nbSlot = glm::vec2(6, 4);
    DrawInventorySlotBackground(position, backgroundSize);
    DrawMultipleSlots(position, backgroundSize, nbSlot, true);
}

void InventorySystem::DrawInventorySlotBackground(const glm::vec2 &position, const glm::vec2 &size)
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
            SpriteRenderer::Draw(SpriteRenderDataBuilder().SetPosition(position + glm::vec2(x, y) * SLOT_SIZE).SetSize(glm::vec2(SLOT_SIZE, SLOT_SIZE)).SetSprite(sprite).SetDrawAbsolute(true).Build());
        }
    }
}

void InventorySystem::DrawMultipleSlots(const glm::vec2 &position, const glm::vec2 &backgroundSize, const glm::vec2 &nbSlot, bool gapOnEdge)
{
    float edge = 2;
    glm::vec2 nbGap;
    if (gapOnEdge)
        nbGap = nbSlot + edge - 1.0f;
    else
        nbGap = nbSlot - 1.0f;
    if (nbGap.x < 1)
        nbGap.x = 1;
    if (nbGap.y < 1)
        nbGap.y = 1;
    glm::vec2 gapSize = (backgroundSize - nbSlot - edge) * SLOT_SIZE / nbGap;

    std::vector<Items> items = {Items::NONE, Items::ITEM_SWORD, Items::ITEM_PICKAXE, Items::ITEM_AXE, Items::ITEM_HOE, Items::WATER_CAN};
    size_t itemCount = 0;
    for (int y = 0; y < nbSlot.y; y++)
    {
        for (int x = 0; x < nbSlot.x; x++)
        {
            Items itemToDraw = Items::NONE;
            if (itemCount < items.size())
                itemToDraw = items[itemCount];
            itemCount++;
            
            glm::vec2 slotPosition;
            if (gapOnEdge)
                slotPosition = position + glm::vec2(x, y) * SLOT_SIZE + glm::vec2(x + 1, y + 1) * gapSize;
            else
                slotPosition = position + glm::vec2(x, y) * SLOT_SIZE + glm::vec2(x, y) * gapSize;
            
            DrawInventorySlot(slotPosition, itemToDraw, slotSelected == glm::vec2(x, y));
        }
    }
}

void InventorySystem::DrawInventorySlot(const glm::vec2 &position, Items item, bool isSelected)
{
    auto texture = RessourceManager::GetTexture("UI_Frames");
    size_t width = texture->getWidth();
    size_t height = texture->getHeight();
    Sprite sprite;
    sprite.textureName = "UI_Frames";
    sprite.textureSize = glm::vec2(width, height) / TILE_SIZE;

    for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            sprite.spriteCoords = glm::vec2(3, 0) + glm::vec2(x, y);
            SpriteRenderer::Draw(SpriteRenderDataBuilder().SetPosition(position + glm::vec2(x, y) * SLOT_SIZE).SetSize(glm::vec2(SLOT_SIZE, SLOT_SIZE)).SetSprite(sprite).SetDrawAbsolute(true).Build());
        }
    }

    if (item != Items::NONE)
        SpriteRenderer::Draw(SpriteRenderDataBuilder().SetPosition(position + glm::vec2(SLOT_SIZE, SLOT_SIZE)).SetSize(glm::vec2(SLOT_SIZE, SLOT_SIZE)).SetSprite(ItemDictionnary::GetItem(item)).SetDrawAbsolute(true).Build());
    if (isSelected)
    {
        texture = RessourceManager::GetTexture("UI_Selectors");
        sprite.textureName = "UI_Selectors";
        sprite.textureSize = glm::vec2(texture->getWidth(), texture->getHeight()) / TILE_SIZE;
        glm::vec2 selectorPos = glm::vec2(1, 12) * 3.0f;
        for (int x = 0; x < 3; x++)
        {
            for (int y = 0; y < 3; y++)
            {
                sprite.spriteCoords = selectorPos + glm::vec2(x, y);
                SpriteRenderer::Draw(SpriteRenderDataBuilder().SetPosition(position + glm::vec2(x, y) * SLOT_SIZE).SetSize(glm::vec2(SLOT_SIZE, SLOT_SIZE)).SetSprite(sprite).SetDrawAbsolute(true).Build());
            }
        }
    }
}

int InventorySystem::DetermineSpriteCoord(int coord, int size)
{
    if (coord == 0)
        return (0);
    else if (coord == size)
        return (2);
    else
        return (1);
}
