#pragma once

#include <array>
#include "globals.hpp"
#include "Game/ItemDictionnary/ItemDictionnary.hpp"

struct ItemSlot
{
    Items item;
    size_t nbItem;
};

class InventorySystem
{
    protected:
        std::array<ItemSlot, INVENTORY_SIZE> inventory;

    public:
        InventorySystem();
        ~InventorySystem();
};