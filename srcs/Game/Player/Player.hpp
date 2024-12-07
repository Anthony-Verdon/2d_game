#pragma once

#include "Engine/PhysicBody/PhysicBody.hpp"
#include "Engine/Animator/Animator.hpp"
#include "Game/PlayerTools/APlayerTool/APlayerTool.hpp"
#include <glm/glm.hpp>
#include <vector>

constexpr glm::vec2 SWORD_HITBOX_SIZE = glm::vec2(32, 96);
constexpr float SWORD_HITBOX_OFFSET = 48;

enum PlayerState
{
    IDLE,
    RUN,
    ATTACK,
    MINING,
};

class Player
{
    private:
        glm::vec2 size;
        glm::vec2 direction;
        PlayerState state;

        Animator bodyAnimator;
        Animator toolAnimator;
        PhysicBody body;
        std::unique_ptr<APlayerTool> tool;
        
        void InitAnimations();

        bool Move();

    public:
        Player();
        ~Player();

        void Init(b2WorldId worldId);
        void Update();
        void Draw();
        glm::vec2 GetPosition() const;
};