#pragma once

#include "Engine/2D/PhysicBody/PhysicBody.hpp"
#include "Game/Items/ItemBehavior/AItemBehavior/AItemBehavior.hpp"
#include "Engine/2D/Animator2D/Animator2D.hpp"
#include "Game/Player/Inventory/InventoryUI/InventoryUI.hpp"

#include <vector>

const ml::vec2 SWORD_HITBOX_SIZE = ml::vec2(32, 96);
constexpr float SWORD_HITBOX_OFFSET = 48;

class Player
{
  private:
    enum StateType
    {
        IDLE_WALK,
        ATTACK,
        USING_TOOL,
        INVENTORY
    };

    class AState
    {
        StateType stateType;

      public:
        AState(StateType stateType) { this->stateType = stateType; }
        virtual ~AState() {}

        virtual void Enter(Player &player) { (void)player; }
        virtual std::unique_ptr<AState> Input(Player &player)
        {
            (void)player;
            return (NULL);
        }
        virtual std::unique_ptr<AState> Update(Player &player)
        {
            (void)player;
            return (NULL);
        }
        virtual void Exit(Player &player) { (void)player; }
        StateType GetStateType() const { return stateType; }

        friend Player;
    };

    class IdleWalkState;
    class AttackState;
    class UsingToolState;
    class InventoryState;

    ml::vec2 size;
    ml::vec2 direction;

    Animator2D bodyAnimationManager;
    Animator2D toolAnimationManager;
    PhysicBody body;
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
    ml::vec2 GetPosition() const;
    ItemType GetItemSelected() const { return (inventoryUI.GetItemSelected()); }
};