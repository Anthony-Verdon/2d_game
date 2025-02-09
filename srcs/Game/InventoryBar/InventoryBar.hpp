#pragma once

#include "Game/Player/Player.hpp"

class InventoryBar
{
    private:
        void DrawInventorySlot(const glm::vec2 &position);
        
    public:
        InventoryBar();
        ~InventoryBar();

        void Draw(const Player &player);
};