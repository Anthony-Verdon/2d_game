#pragma once

#include "Game/Items/ItemBehavior/AItemBehavior/AItemBehavior.hpp"

class PickaxeBehavior : public AItemBehavior
{
  public:
    PickaxeBehavior();
    ~PickaxeBehavior();

    void MainAction(const ml::vec2 &actionCoords);
};