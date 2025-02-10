#pragma once

#include "Game/Player/Player.hpp"
#include "Game/ItemDictionnary/ItemDictionnary.hpp"

class InventoryBar
{
    private:
        glm::vec2 slotSelected;

        void DrawInventorySlotBackground(const glm::vec2 &position, const glm::vec2 &size);
        void DrawMultipleSlots(const glm::vec2 &position, const glm::vec2 &backgroundSize, const glm::vec2 &nbSlot, bool gapOnEdge);
        void DrawInventorySlot(const glm::vec2 &position, Items item, bool isSelected);
        int DetermineSpriteCoord(int coord, int size);

    public:
        InventoryBar();
        ~InventoryBar();

        void SetSlotSelected(const glm::vec2 &slotSelected) {this->slotSelected = slotSelected;}
        void Draw(const Player &player);
};