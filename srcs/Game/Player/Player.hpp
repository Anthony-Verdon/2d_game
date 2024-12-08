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
        class AState
        {
            protected:

            public:
                AState() {}
                virtual ~AState() {}

                virtual void Enter() {}
                virtual std::unique_ptr<AState> Input() { return (NULL); }
                virtual std::unique_ptr<AState> Update() { return (NULL); }
                virtual void Exit() {}
        };

        class IdleState;
        class WalkState;
        
        glm::vec2 size;
        glm::vec2 direction;

        Animator bodyAnimator;
        Animator toolAnimator;
        PhysicBody body;
        std::unique_ptr<APlayerTool> tool;
        std::unique_ptr<AState> statePtr;
        PlayerState state;
        
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