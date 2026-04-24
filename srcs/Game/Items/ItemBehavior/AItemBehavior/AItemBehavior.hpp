#pragma once

#include "Matrix/Matrix.hpp"

class AItemBehavior
{
  public:
    AItemBehavior() {}
    virtual ~AItemBehavior() {}

    virtual void MainAction(const ml::vec2 &actionCoords = ml::vec2(0, 0)) { (void)actionCoords; }
};