#include "Game/Player/Inventory/InventorySystem/InventorySystem.hpp"

InventorySystem::InventorySystem()
{
    for (auto it = inventory.begin(); it != inventory.end(); it++)
    {
        it->item = Items::NONE;
        it->nbItem = 0;
    }

    inventory[1] = {Items::ITEM_SWORD, 1};
    inventory[2] = {Items::ITEM_PICKAXE, 1};
    inventory[3] = {Items::ITEM_AXE, 1};
    inventory[4] = {Items::ITEM_HOE, 1};
    inventory[5] = {Items::WATER_CAN, 1};
}

InventorySystem::~InventorySystem()
{

}