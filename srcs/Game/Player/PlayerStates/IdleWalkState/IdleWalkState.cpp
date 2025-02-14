#include "Game/Player/PlayerStates/IdleWalkState/IdleWalkState.hpp"
#include "Game/Player/PlayerStates/AttackState/AttackState.hpp"
#include "Game/Player/PlayerStates/UsingToolState/UsingToolState.hpp"
#include "Game/Player/PlayerStates/InventoryState/InventoryState.hpp"
#include "Engine/WindowManager/WindowManager.hpp"
#include "Engine/Time/Time.hpp"

Player::IdleWalkState::IdleWalkState(): Player::AState(Player::StateType::IDLE_WALK)
{
   velocity = glm::vec2(0, 0);
}

Player::IdleWalkState::~IdleWalkState()
{
}

void Player::IdleWalkState::Enter(Player &player)
{
    player.bodyAnimationManager.Play("idle_" + player.DetermineDirectionString());
}

std::unique_ptr<Player::AState> Player::IdleWalkState::Input(Player &player)
{
    if (WindowManager::IsInputPressedOrMaintain(GLFW_MOUSE_BUTTON_1))
    {
        switch (player.GetItemSelected())
        {
            case ItemType::SWORD:
                return (std::make_unique<Player::AttackState>());
            case ItemType::PICKAXE:
                return (std::make_unique<Player::UsingToolState>("mining_", "pickaxe_"));
            case ItemType::AXE:
                return (std::make_unique<Player::UsingToolState>("chopping_", "axe_"));
            case ItemType::HOE:
                return (std::make_unique<Player::UsingToolState>("plowing_", "hoe_"));
            case ItemType::WATERING_CAN:
                return (std::make_unique<Player::UsingToolState>("watering_", "watering_can_"));
            default:
                return (NULL);
        }
    }
    
    if (WindowManager::IsInputPressed(GLFW_KEY_E))
        return (std::make_unique<Player::InventoryState>());

    velocity.x = WindowManager::IsInputPressedOrMaintain(GLFW_KEY_D) - WindowManager::IsInputPressedOrMaintain(GLFW_KEY_A);
    velocity.y = WindowManager::IsInputPressedOrMaintain(GLFW_KEY_S) - WindowManager::IsInputPressedOrMaintain(GLFW_KEY_W);
    if (velocity != glm::vec2(0, 0))
    {   
        // keep the direction if the direction key is still pushed
        // else update it
        if (player.direction.y != 0 && velocity.y != 0)
        {
            player.direction.x = 0;
            player.direction.y = velocity.y;
        }
        else if (player.direction.x != 0 && velocity.x != 0)
        {
            player.direction.x = velocity.x;
            player.direction.y = 0;
        }
        else if (velocity.y != 0)
        {
            player.direction.x = 0;
            player.direction.y = velocity.y;
        }
        else
        {
            player.direction.x = velocity.x;
            player.direction.y = 0;
        }
    }
    
    return (NULL);
}

std::unique_ptr<Player::AState> Player::IdleWalkState::Update(Player &player)
{
    if (velocity != glm::vec2(0, 0))
    {
        velocity = glm::normalize(velocity) * 200.0f * Time::getDeltaTime();
        player.bodyAnimationManager.Play("walk_" + player.DetermineDirectionString());
    }
    else
    {
        player.bodyAnimationManager.Play("idle_" + player.DetermineDirectionString());
    }

    b2Body_SetLinearVelocity(player.body.GetBodyId(), {velocity.x, velocity.y});

    return (NULL);
}