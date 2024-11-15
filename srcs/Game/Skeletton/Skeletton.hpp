#pragma once

#include "Engine/PhysicBody/PhysicBody.hpp"
#include "Engine/Animator/Animator.hpp"

class Skeletton
{
    private:
        glm::vec2 size;
        Animator animator;
        PhysicBody body;
        
        void InitAnimations();

    public:
        Skeletton();
        ~Skeletton();

        void Init(b2WorldId worldId);
        void Draw();
};