#pragma once

#include "Engine/2D/PhysicBody/PhysicBody.hpp"

class Barrel
{
  private:
    ml::vec2 size;
    PhysicBody body;

  public:
    Barrel();
    ~Barrel();

    void Draw();
    void Init(b2WorldId worldId);
};