#include "Game/Player/PlayerStates/MiningState/MiningState.hpp"
#include "Game/Player/PlayerStates/IdleWalkState/IdleWalkState.hpp"
#include "Game/CategoriesFilter.hpp"
#include "Engine/WindowManager/WindowManager.hpp"
#include <iostream>

Player::MiningState::MiningState(): Player::AState()
{
}

Player::MiningState::~MiningState()
{
}

void Player::MiningState::Enter(Player &player)
{
    player.bodyAnimator.Play("mining" + player.DetermineDirectionString());
    player.toolAnimator.Play("iron_pickaxe" + player.DetermineDirectionString());
    b2Body_SetLinearVelocity(player.body.GetBodyId(), {0, 0});
}

std::unique_ptr<Player::AState> Player::MiningState::Update(Player &player)
{
    if (!player.bodyAnimator.CurrentAnimationEnded())
        return (NULL);
    
    player.toolAnimator.Play("none");
    return (std::make_unique<Player::IdleWalkState>());
}