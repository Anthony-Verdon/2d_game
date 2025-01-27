#include "Game/Player/PlayerStates/WateringState/WateringState.hpp"
#include "Game/Player/PlayerStates/IdleWalkState/IdleWalkState.hpp"

Player::WateringState::WateringState(): Player::AState(Player::StateType::PLOWING)
{
}

Player::WateringState::~WateringState()
{
}

void Player::WateringState::Enter(Player &player)
{
    player.bodyAnimationManager.Play("watering_" + player.DetermineDirectionString());
    player.toolAnimationManager.Play("watering_can_" + player.DetermineDirectionString());
    b2Body_SetLinearVelocity(player.body.GetBodyId(), {0, 0});
}

std::unique_ptr<Player::AState> Player::WateringState::Update(Player &player)
{
    if (!player.bodyAnimationManager.CurrentAnimationEnded())
        return (NULL);
    
    player.toolAnimationManager.Play("none");
    return (std::make_unique<Player::IdleWalkState>());
}