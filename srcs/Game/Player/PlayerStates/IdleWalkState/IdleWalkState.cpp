#include "Game/Player/PlayerStates/IdleWalkState/IdleWalkState.hpp"
#include "Game/Player/PlayerStates/AttackState/AttackState.hpp"
#include "Engine/WindowManager/WindowManager.hpp"
#include "Engine/Time/Time.hpp"

Player::IdleWalkState::IdleWalkState(): Player::AState()
{
}

Player::IdleWalkState::~IdleWalkState()
{
}

void Player::IdleWalkState::Enter(Player &player)
{
    player.bodyAnimator.Play("idle" + player.DetermineDirectionString());
}

std::unique_ptr<Player::AState> Player::IdleWalkState::Input(Player &player)
{
    if (WindowManager::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_1))
        return (std::make_unique<Player::AttackState>());

    velocity.x = WindowManager::IsKeyPressed(GLFW_KEY_D) - WindowManager::IsKeyPressed(GLFW_KEY_A);
    velocity.y = WindowManager::IsKeyPressed(GLFW_KEY_S) - WindowManager::IsKeyPressed(GLFW_KEY_W);
    if (velocity != glm::vec2(0, 0))
        player.direction = velocity;
    
    return (NULL);
}

std::unique_ptr<Player::AState> Player::IdleWalkState::Update(Player &player)
{
    if (velocity != glm::vec2(0, 0))
    {
        velocity = glm::normalize(velocity) * 200.0f * Time::getDeltaTime();
        player.bodyAnimator.Play("walk" + player.DetermineDirectionString());
    }
    else
    {
        player.bodyAnimator.Play("idle" + player.DetermineDirectionString());
    }

    b2Body_SetLinearVelocity(player.body.GetBodyId(), {velocity.x, velocity.y});

    return (NULL);
}