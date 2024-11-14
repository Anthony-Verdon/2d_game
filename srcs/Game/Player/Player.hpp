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
        glm::vec2 direction;

        Animator bodyAnimator;
        Animator toolAnimator;
        PhysicBody body;
        
        void InitAnimations();

        void Move();
        void UpdateSwordHitbox();

    public:
        Player();
        ~Player();

        void Init(b2WorldId worldId);
        void Update();
        void Draw();
        glm::vec2 GetPosition() const;
};