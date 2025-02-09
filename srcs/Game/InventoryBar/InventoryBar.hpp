#pragma once

#include "Game/Player/Player.hpp"

class InventoryBar
{
    public:
        InventoryBar();
        ~InventoryBar();

        void Draw(const Player &player);
};