#include "Game/Player/PlayerStates/UsingToolState/UsingToolState.hpp"
#include "Game/Player/PlayerStates/IdleWalkState/IdleWalkState.hpp"

Player::UsingToolState::UsingToolState(const std::string &bodyAnim, const std::string &toolAnim): Player::AState(Player::StateType::USING_TOOL)
{
    this->bodyAnim = bodyAnim;
    this->toolAnim = toolAnim;
}

Player::UsingToolState::~UsingToolState()
{
}

void Player::UsingToolState::Enter(Player &player)
{
    player.bodyAnimationManager.Play(bodyAnim + player.DetermineDirectionString());
    player.toolAnimationManager.Play(toolAnim + player.DetermineDirectionString());
    b2Body_SetLinearVelocity(player.body.GetBodyId(), {0, 0});

    glm::vec2 playerPos = player.GetPosition();
    if (playerPos.x < 0)
        playerPos.x -= SPRITE_SIZE;
    if (playerPos.y < 0)
        playerPos.y -= SPRITE_SIZE;
    glm::vec2 actionCoords = glm::vec2(((int)playerPos.x / (int)SPRITE_SIZE + player.direction.x) * SPRITE_SIZE, ((int)playerPos.y / (int)SPRITE_SIZE + player.direction.y) * SPRITE_SIZE) + SPRITE_SIZE / 2;

    ItemDictionnary::ExecuteBehavior(player.GetItemSelected(), actionCoords);
}

std::unique_ptr<Player::AState> Player::UsingToolState::Update(Player &player)
{
    if (!player.bodyAnimationManager.CurrentAnimationEnded())
        return (NULL);
    
    player.toolAnimationManager.Play("none");
    return (std::make_unique<Player::IdleWalkState>());
}