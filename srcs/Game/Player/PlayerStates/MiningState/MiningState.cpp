#include "Game/Player/PlayerStates/MiningState/MiningState.hpp"
#include "Game/Player/PlayerStates/IdleWalkState/IdleWalkState.hpp"
#include "Game/Items/ItemDictionnary/ItemDictionnary.hpp"
#include "globals.hpp"

Player::MiningState::MiningState(): Player::AState(Player::StateType::MINING)
{
}

Player::MiningState::~MiningState()
{
}

void Player::MiningState::Enter(Player &player)
{
    player.bodyAnimationManager.Play("mining_" + player.DetermineDirectionString());
    player.toolAnimationManager.Play("pickaxe_" + player.DetermineDirectionString());
    b2Body_SetLinearVelocity(player.body.GetBodyId(), {0, 0});

    glm::vec2 playerPos = player.GetPosition();
    if (playerPos.x < 0)
        playerPos.x -= SPRITE_SIZE;
    if (playerPos.y < 0)
        playerPos.y -= SPRITE_SIZE;
    glm::vec2 actionCoords = glm::vec2(((int)playerPos.x / (int)SPRITE_SIZE + player.direction.x) * SPRITE_SIZE, ((int)playerPos.y / (int)SPRITE_SIZE + player.direction.y) * SPRITE_SIZE) + SPRITE_SIZE / 2;
    ItemDictionnary::ExecuteBehavior(player.GetItemSelected(), actionCoords);
}

std::unique_ptr<Player::AState> Player::MiningState::Update(Player &player)
{
    if (!player.bodyAnimationManager.CurrentAnimationEnded())
        return (NULL);
    
    player.toolAnimationManager.Play("none");
    return (std::make_unique<Player::IdleWalkState>());
}