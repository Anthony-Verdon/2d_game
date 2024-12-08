#include "Game/Player/PlayerStates/AttackState/AttackState.hpp"
#include "Game/Player/PlayerStates/IdleState/IdleState.hpp"
#include "Game/Player/PlayerStates/WalkState/WalkState.hpp"
#include "Engine/WindowManager/WindowManager.hpp"
#include <iostream>

Player::AttackState::AttackState(): Player::AState()
{
}

Player::AttackState::~AttackState()
{
}

void Player::AttackState::Enter(Player &player)
{
    player.bodyAnimator.Play("attack1" + player.DetermineDirectionString());
    player.toolAnimator.Play("iron_sword_attack1" + player.DetermineDirectionString());
    b2Body_SetLinearVelocity(player.body.GetBodyId(), {0, 0});
}

std::unique_ptr<Player::AState> Player::AttackState::Update(Player &player)
{
    if (!player.bodyAnimator.CurrentAnimationEnded())
        return (NULL);
    
    player.toolAnimator.Play("none");
    glm::vec2 newDirection;
    newDirection.x = WindowManager::IsKeyPressed(GLFW_KEY_D) - WindowManager::IsKeyPressed(GLFW_KEY_A);
    newDirection.y = WindowManager::IsKeyPressed(GLFW_KEY_S) - WindowManager::IsKeyPressed(GLFW_KEY_W);
    if (newDirection == glm::vec2(0, 0))
        return (std::make_unique<Player::IdleState>());
    else
    {
        player.direction = newDirection;
        return (std::make_unique<Player::WalkState>());
    }
}