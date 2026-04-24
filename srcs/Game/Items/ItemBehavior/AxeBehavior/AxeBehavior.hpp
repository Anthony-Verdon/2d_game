#pragma once

#include "Game/Items/ItemBehavior/AItemBehavior/AItemBehavior.hpp"

class AxeBehavior : public AItemBehavior
{
  public:
    AxeBehavior();
    ~AxeBehavior();

    void MainAction(const ml::vec2 &actionCoords);
};