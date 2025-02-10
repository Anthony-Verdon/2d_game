#pragma once

#include "Game/Player/Player.hpp"

class InventoryBar
{
    private:
        void DrawInventorySlotBackground(const glm::vec2 &position, const glm::vec2 &size);
        void DrawMultipleSlots(const glm::vec2 &position, const glm::vec2 &backgroundSize, const glm::vec2 &nbSlot);
        void DrawInventorySlot(const glm::vec2 &position);
        int DetermineSpriteCoord(int coord, int size);

    public:
        InventoryBar();
        ~InventoryBar();

        void Draw(const Player &player);
};