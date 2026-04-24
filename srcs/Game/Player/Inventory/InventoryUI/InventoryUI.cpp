#include "Game/Player/Inventory/InventoryUI/InventoryUI.hpp"
#include "Game/Player/Player.hpp"
#include "Engine/RessourceManager/RessourceManager.hpp"
#include "Engine/WindowManager/WindowManager.hpp"
#include "Engine/2D/Renderers/SpriteRenderer/SpriteRenderer.hpp"
#include "Engine/2D/Renderers/PolygonRenderer/PolygonRenderer.hpp"
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
        // @PROBLEM
        SpriteRenderer::Draw(SpriteRenderDataBuilder().SetPosition(WindowManager::GetMousePosition()).SetSize(ml::vec2(SLOT_SIZE, SLOT_SIZE) * 1.5f).SetSprite(ItemDictionnary::GetItemSprite(itemHold)).SetDrawAbsolute(true) /*.SetOpacity(0.5)*/.Build());
    }
}

void InventoryUI::DrawInventoryBar()
{
    ml::vec2 backgroundSize = ml::vec2(12, 3);
    ml::vec2 position = ml::vec2(WindowManager::GetWindowWidth() / 2.0f - backgroundSize.x / 2.0f * SLOT_SIZE, WindowManager::GetWindowHeight() - SLOT_SIZE * 2.0f);
    ml::vec2 nbSlot = ml::vec2(INVENTORY_WIDTH, INVENTORY_BAR_HEIGHT);
    DrawInventorySlotBackground(position, backgroundSize);
    DrawMultipleSlots(position, backgroundSize, nbSlot, true);
}

void InventoryUI::DrawFullInventory()
{
    PolygonRenderer::Draw("square", WindowManager::GetWindowSize() / 2.0f, WindowManager::GetWindowSize(), 0, ml::vec4(0, 0, 0, 0.5), ml::vec4(0, 0, 0, 0), true);
    ml::vec2 backgroundSize = ml::vec2(12, 3);
    ml::vec2 position = WindowManager::GetWindowSize() / 2.0f - backgroundSize / 2.0f * SLOT_SIZE - ml::vec2(0, 2 * SLOT_SIZE);
    ml::vec2 nbSlot = ml::vec2(INVENTORY_WIDTH, INVENTORY_BAR_HEIGHT);
    DrawInventorySlotBackground(position, backgroundSize);
    DrawMultipleSlots(position, backgroundSize, nbSlot, true);

    backgroundSize = ml::vec2(12, 7);
    position = position + ml::vec2(0, 2 * SLOT_SIZE);
    nbSlot = ml::vec2(INVENTORY_WIDTH, INVENTORY_EXPANDED_HEIGHT);
    DrawInventorySlotBackground(position, backgroundSize);
    DrawMultipleSlots(position, backgroundSize, nbSlot, true);
}

void InventoryUI::DrawInventorySlotBackground(const ml::vec2 &position, const ml::vec2 &size)
{
    auto texture = RessourceManager::GetTexture("UI_Frames");
    size_t width = texture->getWidth();
    size_t height = texture->getHeight();
    Sprite sprite;
    sprite.textureName = "UI_Frames";
    sprite.textureSize = ml::vec2(width, height) / TILE_SIZE;

    for (int x = 0; x < size.x; x++)
    {
        for (int y = 0; y < size.y; y++)
        {
            sprite.spriteCoords.x = DetermineSpriteCoord(x, size.x - 1);
            sprite.spriteCoords.y = DetermineSpriteCoord(y, size.y - 1);
            SpriteRenderer::Draw(SpriteRenderDataBuilder().SetPosition(position + ml::vec2(x, y) * SLOT_SIZE).SetSize(ml::vec2(SLOT_SIZE, SLOT_SIZE)).SetSprite(sprite).SetDrawAbsolute(true).Build());
        }
    }
}

void InventoryUI::DrawMultipleSlots(const ml::vec2 &position, const ml::vec2 &backgroundSize, const ml::vec2 &nbSlot, bool gapOnEdge)
{
    float edge = 2;
    ml::vec2 nbGap;
    if (gapOnEdge)
        nbGap = nbSlot + ml::vec2(edge - 1.0f, edge - 1.0f);
    else
        nbGap = nbSlot - ml::vec2(1.0f, 1.0f);
    if (nbGap.x < 1)
        nbGap.x = 1;
    if (nbGap.y < 1)
        nbGap.y = 1;
    ml::vec2 gapSize = (backgroundSize - nbSlot - ml::vec2(edge, edge)) * SLOT_SIZE;
    gapSize.x = gapSize.x / nbGap.x;
    gapSize.y = gapSize.y / nbGap.y;

    for (int y = 0; y < nbSlot.y; y++)
    {
        for (int x = 0; x < nbSlot.x; x++)
        {
            ItemType itemToDraw = ItemType::NONE;
            if (itemCount < inventory.size())
                itemToDraw = inventory[itemCount].item;

            ml::vec2 slotPosition;
            if (gapOnEdge)
                slotPosition = position + ml::vec2(x, y) * SLOT_SIZE + ml::vec2(x + 1, y + 1) * gapSize;
            else
                slotPosition = position + ml::vec2(x, y) * SLOT_SIZE + ml::vec2(x, y) * gapSize;

            DrawInventorySlot(slotPosition, itemToDraw, slotSelected == itemCount);
            itemCount++;
        }
    }
}

void InventoryUI::DrawInventorySlot(const ml::vec2 &position, ItemType item, bool isSelected)
{
    auto texture = RessourceManager::GetTexture("UI_Frames");
    size_t width = texture->getWidth();
    size_t height = texture->getHeight();
    Sprite sprite;
    sprite.textureName = "UI_Frames";
    sprite.textureSize = ml::vec2(width, height) / TILE_SIZE;

    // draw frame
    for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            sprite.spriteCoords = ml::vec2(3, 0) + ml::vec2(x, y);
            SpriteRenderer::Draw(SpriteRenderDataBuilder().SetPosition(position + ml::vec2(x, y) * SLOT_SIZE).SetSize(ml::vec2(SLOT_SIZE, SLOT_SIZE)).SetSprite(sprite).SetDrawAbsolute(true).Build());
        }
    }

    // if hovering slot, the item inside is scaled
    // if clicking on it, move the selector and store it
    // and store the value for drag and drop
    // else if not clicking and holding an item, drop it
    ml::vec2 slotPos = position + ml::vec2(SLOT_SIZE, SLOT_SIZE);
    ml::vec2 slotSize = ml::vec2(SLOT_SIZE, SLOT_SIZE);
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
        sprite.textureSize = ml::vec2(texture->getWidth(), texture->getHeight()) / TILE_SIZE;
        ml::vec2 selectorPos = ml::vec2(1, 12) * 3.0f;
        for (int x = 0; x < 3; x++)
        {
            for (int y = 0; y < 3; y++)
            {
                sprite.spriteCoords = selectorPos + ml::vec2(x, y);
                SpriteRenderer::Draw(SpriteRenderDataBuilder().SetPosition(position + ml::vec2(x, y) * SLOT_SIZE).SetSize(ml::vec2(SLOT_SIZE, SLOT_SIZE)).SetSprite(sprite).SetDrawAbsolute(true).Build());
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
