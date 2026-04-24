#pragma once

#include "Game/Items/ItemBehavior/AItemBehavior/AItemBehavior.hpp"

class SwordBehavior : public AItemBehavior
{
  public:
    SwordBehavior();
    ~SwordBehavior();

    void MainAction(const ml::vec2 &actionCoords);
};