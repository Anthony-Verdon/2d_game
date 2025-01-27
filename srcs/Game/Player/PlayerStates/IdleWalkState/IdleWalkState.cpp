#include "Game/Player/PlayerStates/IdleWalkState/IdleWalkState.hpp"
#include "Game/Player/PlayerStates/AttackState/AttackState.hpp"
#include "Game/Player/PlayerStates/MiningState/MiningState.hpp"
#include "Game/Player/PlayerStates/ChoppingState/ChoppingState.hpp"
#include "Game/Player/PlayerStates/PlowingState/PlowingState.hpp"
#include "Engine/WindowManager/WindowManager.hpp"
#include "Engine/Time/Time.hpp"

Player::IdleWalkState::IdleWalkState(): Player::AState(Player::StateType::IDLE_WALK)
{
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
    if (WindowManager::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_1))
    {
        if (!player.tool)
            return (NULL);

        switch (player.tool->GetType())
        {
            case PlayerTool::SWORD:
                return (std::make_unique<Player::AttackState>());
            case PlayerTool::PICKAXE:
                return (std::make_unique<Player::MiningState>());
            case PlayerTool::AXE:
                return (std::make_unique<Player::ChoppingState>());
            case PlayerTool::HOE:
                return (std::make_unique<Player::PlowingState>());
            default:
                return (NULL);
        }

    }

    velocity.x = WindowManager::IsKeyPressed(GLFW_KEY_D) - WindowManager::IsKeyPressed(GLFW_KEY_A);
    velocity.y = WindowManager::IsKeyPressed(GLFW_KEY_S) - WindowManager::IsKeyPressed(GLFW_KEY_W);
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