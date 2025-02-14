#pragma once

#include "Engine/UI/Button/Button.hpp"
#include "Game/Items/ItemDictionnary/ItemDictionnary.hpp"
#include "Game/Player/Inventory/InventorySystem/InventorySystem.hpp"

class Player;

class InventoryUI: public InventorySystem
{
    private:
        bool open;
        size_t slotSelected;
        size_t itemCount;
        ItemType itemHold;
        size_t itemHoldPosition;
        bool resetItemHold;

        void DrawInventoryBar();
        void DrawFullInventory();

        void DrawInventorySlotBackground(const glm::vec2 &position, const glm::vec2 &size);
        void DrawMultipleSlots(const glm::vec2 &position, const glm::vec2 &backgroundSize, const glm::vec2 &nbSlot, bool gapOnEdge);
        void DrawInventorySlot(const glm::vec2 &position, ItemType item, bool isSelected);
        int DetermineSpriteCoord(int coord, int size);
    public:
        InventoryUI();
        ~InventoryUI();

        void SetSlotSelected(size_t slotSelected) {this->slotSelected = slotSelected;}
        void SetOpen(bool open) {this->open = open;}
        void Draw(const Player &player);
        ItemType GetItemSelected() const {return (inventory[slotSelected].item); }
};