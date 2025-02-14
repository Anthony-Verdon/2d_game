#include "Game/Player/Inventory/InventorySystem/InventorySystem.hpp"

InventorySystem::InventorySystem()
{
    for (auto it = inventory.begin(); it != inventory.end(); it++)
    {
        it->item = ItemType::NONE;
        it->nbItem = 0;
    }

    inventory[1] = {ItemType::ITEM_SWORD, 1};
    inventory[2] = {ItemType::ITEM_PICKAXE, 1};
    inventory[3] = {ItemType::ITEM_AXE, 1};
    inventory[4] = {ItemType::ITEM_HOE, 1};
    inventory[5] = {ItemType::WATER_CAN, 1};
}

InventorySystem::~InventorySystem()
{

}