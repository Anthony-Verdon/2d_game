#pragma once

#include "Engine/PhysicBody/PhysicBody.hpp"
#include "Engine/Animator/Animator.hpp"
#include <glm/glm.hpp>
#include <vector>

constexpr glm::vec2 SWORD_HITBOX_SIZE = glm::vec2(16, 16);
constexpr float SWORD_HITBOX_OFFSET = 48;

class Player
{
    private:
        glm::vec2 size;
        Animator animator;
        
        PhysicBody body;
        
    public:
        Player();
        ~Player();

        void Draw();
        void Move(const glm::vec2 &amount);
        void Init(b2WorldId worldId);
        glm::vec2 GetPosition() const;
};