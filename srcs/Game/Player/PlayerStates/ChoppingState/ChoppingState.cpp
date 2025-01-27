#include "Game/Player/PlayerStates/ChoppingState/ChoppingState.hpp"
#include "Game/Player/PlayerStates/IdleWalkState/IdleWalkState.hpp"

Player::ChoppingState::ChoppingState(): Player::AState(Player::StateType::CHOPPING)
{
}

Player::ChoppingState::~ChoppingState()
{
}

void Player::ChoppingState::Enter(Player &player)
{
    player.bodyAnimationManager.Play("chopping_" + player.DetermineDirectionString());
    player.toolAnimationManager.Play("axe_" + player.DetermineDirectionString());
    b2Body_SetLinearVelocity(player.body.GetBodyId(), {0, 0});
}

std::unique_ptr<Player::AState> Player::ChoppingState::Update(Player &player)
{
    if (!player.bodyAnimationManager.CurrentAnimationEnded())
        return (NULL);
    
    player.toolAnimationManager.Play("none");
    return (std::make_unique<Player::IdleWalkState>());
}