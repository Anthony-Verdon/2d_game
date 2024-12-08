#include "Game/Player/PlayerStates/AttackState/AttackState.hpp"
#include "Game/Player/PlayerStates/IdleWalkState/IdleWalkState.hpp"
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
    return (std::make_unique<Player::IdleWalkState>());
}