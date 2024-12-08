#pragma once

#include "Engine/PhysicBody/PhysicBody.hpp"
#include "Engine/Animator/Animator.hpp"
#include "Game/PlayerTools/APlayerTool/APlayerTool.hpp"
#include <glm/glm.hpp>
#include <vector>

constexpr glm::vec2 SWORD_HITBOX_SIZE = glm::vec2(32, 96);
constexpr float SWORD_HITBOX_OFFSET = 48;

class Player
{
    private:
        class AState
        {
            public:
                AState() {}
                virtual ~AState() {}

                virtual void Enter(Player &player) {(void)player;}
                virtual std::unique_ptr<AState> Input(Player &player) { (void)player; return (NULL); }
                virtual std::unique_ptr<AState> Update(Player &player) { (void)player; return (NULL); }
                virtual void Exit(Player &player) {(void)player;}
            
            friend Player;
        };

        class IdleWalkState;
        class AttackState;
        
        glm::vec2 size;
        glm::vec2 direction;

        Animator bodyAnimator;
        Animator toolAnimator;
        PhysicBody body;
        std::unique_ptr<APlayerTool> tool;
        std::unique_ptr<AState> state;

        void InitAnimations();
        std::string DetermineDirectionString() const;

    public:
        Player();
        ~Player();

        void Init(b2WorldId worldId);
        void Update();
        void Draw();
        glm::vec2 GetPosition() const;
};