#include "Game/Player/Inventory/InventoryUI/InventoryUI.hpp"
#include "Game/Player/Player.hpp"
#include "Engine/RessourceManager/RessourceManager.hpp"
#include "Engine/WindowManager/WindowManager.hpp"
#include "Engine/Renderers/SpriteRenderer/SpriteRenderer.hpp"
#include "Engine/Renderers/PolygonRenderer/PolygonRenderer.hpp"
#include "Engine/UI/UI.hpp"
#include "globals.hpp"

InventoryUI::InventoryUI()
{
    RessourceManager::AddTexture("UI_Frames", "assets/UI/UI_Frames.png");
    RessourceManager::AddTexture("UI_Selectors", "assets/UI/UI_Selectors.png");
    
    slotSelected = 0;
    open = false;
    itemHold = ItemType::NONE;
    itemHoldPosition = -1;
}

InventoryUI::~InventoryUI()
{
}

void InventoryUI::Draw(const Player &player)
{
    (void)player;
    itemCount = 0;

    resetItemHold = false;

    if (open)
        DrawFullInventory();
    else
        DrawInventoryBar();

    if (resetItemHold)
    {
        itemHold = ItemType::NONE;
        itemHoldPosition = -1;
    }
    if (itemHold != ItemType::NONE)
    {
        SpriteRenderer::Draw(SpriteRenderDataBuilder().SetPosition(WindowManager::GetMousePosition()).SetSize(glm::vec2(SLOT_SIZE, SLOT_SIZE) * 1.5f).SetSprite(ItemDictionnary::GetItemSprite(itemHold)).SetDrawAbsolute(true).SetOpacity(0.5).Build());
    }
}

void InventoryUI::DrawInventoryBar()
{
    glm::vec2 backgroundSize = glm::vec2(12, 3);
    glm::vec2 position = glm::vec2(WindowManager::GetWindowWidth() / 2.0f - backgroundSize.x / 2.0f * SLOT_SIZE, WindowManager::GetWindowHeight() - SLOT_SIZE * 2.0f);
    glm::vec2 nbSlot = glm::vec2(INVENTORY_WIDTH, INVENTORY_BAR_HEIGHT);
    DrawInventorySlotBackground(position, backgroundSize);
    DrawMultipleSlots(position, backgroundSize, nbSlot, true);
}

void InventoryUI::DrawFullInventory()
{
    PolygonRenderer::Draw("square", WindowManager::GetWindowSize() / 2.0f, WindowManager::GetWindowSize(), 0, glm::vec4(0, 0, 0, 0.5), glm::vec4(0, 0, 0, 0), true);
    glm::vec2 backgroundSize = glm::vec2(12, 3);
    glm::vec2 position = WindowManager::GetWindowSize() / 2.0f - backgroundSize / 2.0f * SLOT_SIZE - glm::vec2(0, 2 * SLOT_SIZE);
    glm::vec2 nbSlot = glm::vec2(INVENTORY_WIDTH, INVENTORY_BAR_HEIGHT);
    DrawInventorySlotBackground(position, backgroundSize);
    DrawMultipleSlots(position, backgroundSize, nbSlot, true);

    backgroundSize = glm::vec2(12, 7);
    position = position + glm::vec2(0, 2 * SLOT_SIZE);
    nbSlot = glm::vec2(INVENTORY_WIDTH, INVENTORY_EXPANDED_HEIGHT);
    DrawInventorySlotBackground(position, backgroundSize);
    DrawMultipleSlots(position, backgroundSize, nbSlot, true);
}

void InventoryUI::DrawInventorySlotBackground(const glm::vec2 &position, const glm::vec2 &size)
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

void InventoryUI::DrawMultipleSlots(const glm::vec2 &position, const glm::vec2 &backgroundSize, const glm::vec2 &nbSlot, bool gapOnEdge)
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

    for (int y = 0; y < nbSlot.y; y++)
    {
        for (int x = 0; x < nbSlot.x; x++)
        {
            ItemType itemToDraw = ItemType::NONE;
            if (itemCount < inventory.size())
                itemToDraw = inventory[itemCount].item;
            
            glm::vec2 slotPosition;
            if (gapOnEdge)
            slotPosition = position + glm::vec2(x, y) * SLOT_SIZE + glm::vec2(x + 1, y + 1) * gapSize;
            else
                slotPosition = position + glm::vec2(x, y) * SLOT_SIZE + glm::vec2(x, y) * gapSize;
        
            DrawInventorySlot(slotPosition, itemToDraw, slotSelected == itemCount);
            itemCount++;
        }
    }
}

void InventoryUI::DrawInventorySlot(const glm::vec2 &position, ItemType item, bool isSelected)
{
    auto texture = RessourceManager::GetTexture("UI_Frames");
    size_t width = texture->getWidth();
    size_t height = texture->getHeight();
    Sprite sprite;
    sprite.textureName = "UI_Frames";
    sprite.textureSize = glm::vec2(width, height) / TILE_SIZE;

    // draw frame
    for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            sprite.spriteCoords = glm::vec2(3, 0) + glm::vec2(x, y);
            SpriteRenderer::Draw(SpriteRenderDataBuilder().SetPosition(position + glm::vec2(x, y) * SLOT_SIZE).SetSize(glm::vec2(SLOT_SIZE, SLOT_SIZE)).SetSprite(sprite).SetDrawAbsolute(true).Build());
        }
    }

    // if hovering slot, the item inside is scaled
    // if clicking on it, move the selector and store it
    // and store the value for drag and drop
    // else if not clicking and holding an item, drop it
    glm::vec2 slotPos = position + glm::vec2(SLOT_SIZE, SLOT_SIZE);
    glm::vec2 slotSize = glm::vec2(SLOT_SIZE, SLOT_SIZE);
    if (UI::PointInRectangle(WindowManager::GetMousePosition(), slotPos, slotSize))
    {
        slotSize = slotSize * 1.5f;
        if (WindowManager::IsInputPressedOrMaintain(GLFW_MOUSE_BUTTON_1))
        {
            slotSelected = itemCount;
            if (WindowManager::IsInputPressedOrMaintain(GLFW_MOUSE_BUTTON_1, 0.1f) && itemHold == ItemType::NONE)
            {
                itemHold = item;
                itemHoldPosition = itemCount;
            }
        }
        else if (itemHold != ItemType::NONE)
        {
            inventory[itemHoldPosition] = inventory[itemCount];
            inventory[itemCount] = {itemHold, 1};
            slotSelected = itemCount;
            itemHold = ItemType::NONE;
            itemHoldPosition = -1;
        }
    }
    else if (WindowManager::IsInputReleased(GLFW_MOUSE_BUTTON_1))
    {
        resetItemHold = true;
    }
    
    // draw item
    if (item != ItemType::NONE && itemHoldPosition != itemCount)
        SpriteRenderer::Draw(SpriteRenderDataBuilder().SetPosition(slotPos).SetSize(slotSize).SetSprite(ItemDictionnary::GetItemSprite(item)).SetDrawAbsolute(true).Build());

    // if item is selected
    // draw selector 
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

int InventoryUI::DetermineSpriteCoord(int coord, int size)
{
    if (coord == 0)
        return (0);
    else if (coord == size)
        return (2);
    else
        return (1);
}
