#pragma once

#include <array>
#include "globals.hpp"
#include "Game/Items/ItemDictionnary/ItemDictionnary.hpp"

struct ItemSlot
{
    ItemType item;
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