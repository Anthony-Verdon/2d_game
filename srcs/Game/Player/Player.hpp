#pragma once


#include "Engine/PhysicBody/PhysicBody.hpp"
#include "Game/ItemBehavior/AItemBehavior/AItemBehavior.hpp"
#include "Engine/AnimationManager/AnimationManager.hpp"
#include "Game/Player/Inventory/InventoryUI/InventoryUI.hpp"
#include <glm/glm.hpp>
#include <vector>

constexpr glm::vec2 SWORD_HITBOX_SIZE = glm::vec2(32, 96);
constexpr float SWORD_HITBOX_OFFSET = 48;

class Player
{
    private:

        enum StateType
        {
            IDLE_WALK, 
            ATTACK,
            MINING,
            CHOPPING,
            PLOWING,
            WATERING,
            INVENTORY
        };

        class AState
        {
            StateType stateType;

            public:
                AState(StateType stateType) {this->stateType = stateType; }
                virtual ~AState() {}

                virtual void Enter(Player &player) {(void)player;}
                virtual std::unique_ptr<AState> Input(Player &player) { (void)player; return (NULL); }
                virtual std::unique_ptr<AState> Update(Player &player) { (void)player; return (NULL); }
                virtual void Exit(Player &player) {(void)player;}
                StateType GetStateType() const { return stateType; }
            
            friend Player;
        };

        class IdleWalkState;
        class AttackState;
        class MiningState;
        class ChoppingState;
        class PlowingState;
        class WateringState;
        class InventoryState;
        
        glm::vec2 size;
        glm::vec2 direction;

        AnimationManager bodyAnimationManager;
        AnimationManager toolAnimationManager;
        PhysicBody body;
        std::unique_ptr<AItemBehavior> tool;
        std::unique_ptr<AState> state;

        InventoryUI inventoryUI;

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