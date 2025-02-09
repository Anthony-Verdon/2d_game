#pragma once

#include "Game/Player/Player.hpp"

class InventoryBar
{
    private:
        void DrawInventorySlot(const glm::vec2 &position, const glm::vec2 &size);
        int DetermineSpriteCoord(int coord, int size);

    public:
        InventoryBar();
        ~InventoryBar();

        void Draw(const Player &player);
};