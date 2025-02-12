#pragma once

#include "Engine/UI/Button/Button.hpp"
#include "Game/ItemDictionnary/ItemDictionnary.hpp"

class Player;

class InventorySystem
{
    private:
        bool open;
        glm::vec2 slotSelected;
        Button button;
        
        void DrawInventorySlotBackground(const glm::vec2 &position, const glm::vec2 &size);
        void DrawMultipleSlots(const glm::vec2 &position, const glm::vec2 &backgroundSize, const glm::vec2 &nbSlot, bool gapOnEdge);
        void DrawInventorySlot(const glm::vec2 &position, Items item, bool isSelected);
        int DetermineSpriteCoord(int coord, int size);

        UIState state;
    public:
        InventorySystem();
        ~InventorySystem();

        void SetSlotSelected(const glm::vec2 &slotSelected) {this->slotSelected = slotSelected;}
        void SetOpen(bool open) {this->open = open;}
        void Draw(const Player &player);
};