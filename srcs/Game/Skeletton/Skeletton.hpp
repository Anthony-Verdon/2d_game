#pragma once

#include "Engine/2D/PhysicBody/PhysicBody.hpp"
#include "Engine/2D/Animator2D/Animator2D.hpp"

class Skeletton
{
  private:
    ml::vec2 size;
    Animator2D animator;
    PhysicBody body;

    void InitAnimations();

  public:
    Skeletton();
    ~Skeletton();

    void Init(b2WorldId worldId);
    void Update();
    void PlayAnimation(const std::string &name);
    void Draw();
};