#pragma once

#include "Engine/PhysicBody/PhysicBody.hpp"
#include "Engine/Animator/Animator.hpp"
#include <glm/glm.hpp>
#include <vector>

class Player
{
    private:
        glm::vec2 size;
        PhysicBody body;
        Animator animator;
        
    public:
        Player();
        ~Player();

        void Draw();
        void Move(const glm::vec2 &amount);
        void Init(b2WorldId worldId);
        glm::vec2 GetPosition() const;
};