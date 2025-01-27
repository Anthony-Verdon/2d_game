#include "Game/Player/PlayerStates/PlowingState/PlowingState.hpp"
#include "Game/Player/PlayerStates/IdleWalkState/IdleWalkState.hpp"

Player::PlowingState::PlowingState(): Player::AState(Player::StateType::PLOWING)
{
}

Player::PlowingState::~PlowingState()
{
}

void Player::PlowingState::Enter(Player &player)
{
    player.bodyAnimationManager.Play("plowing_" + player.DetermineDirectionString());
    player.toolAnimationManager.Play("hoe_" + player.DetermineDirectionString());
    b2Body_SetLinearVelocity(player.body.GetBodyId(), {0, 0});
}

std::unique_ptr<Player::AState> Player::PlowingState::Update(Player &player)
{
    if (!player.bodyAnimationManager.CurrentAnimationEnded())
        return (NULL);
    
    player.toolAnimationManager.Play("none");
    return (std::make_unique<Player::IdleWalkState>());
}