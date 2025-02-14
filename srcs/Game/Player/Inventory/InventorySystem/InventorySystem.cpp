#include "Game/Player/Inventory/InventorySystem/InventorySystem.hpp"

InventorySystem::InventorySystem()
{
    for (auto it = inventory.begin(); it != inventory.end(); it++)
    {
        it->item = ItemType::NONE;
        it->nbItem = 0;
    }

    inventory[1] = {ItemType::SWORD, 1};
    inventory[2] = {ItemType::PICKAXE, 1};
    inventory[3] = {ItemType::AXE, 1};
    inventory[4] = {ItemType::HOE, 1};
    inventory[5] = {ItemType::WATERING_CAN, 1};
}

InventorySystem::~InventorySystem()
{

}