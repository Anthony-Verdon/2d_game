#include "Game/Player/PlayerStates/WalkState/WalkState.hpp"
#include "Game/Player/PlayerStates/IdleState/IdleState.hpp"
#include "Game/Player/PlayerStates/AttackState/AttackState.hpp"
#include "Engine/WindowManager/WindowManager.hpp"
#include "Engine/Time/Time.hpp"
#include <iostream>

Player::WalkState::WalkState(): Player::AState()
{
}

Player::WalkState::~WalkState()
{
}

void Player::WalkState::Enter(Player &player)
{
    std::string directionString = "";
    if (player.direction.y < 0)
        directionString = "Up";
    else if (player.direction.y > 0)
        directionString = "Down";
    else
        directionString = "Side";

    player.bodyAnimator.Play("walk" + directionString);
}

std::unique_ptr<Player::AState> Player::WalkState::Input(Player &player)
{
    if (WindowManager::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_1))
        return (std::make_unique<Player::AttackState>());

    glm::vec2 newDirection;
    newDirection.x = WindowManager::IsKeyPressed(GLFW_KEY_D) - WindowManager::IsKeyPressed(GLFW_KEY_A);
    newDirection.y = WindowManager::IsKeyPressed(GLFW_KEY_S) - WindowManager::IsKeyPressed(GLFW_KEY_W);
    if (newDirection == glm::vec2(0, 0))
        return (std::make_unique<Player::IdleState>());
    else
    {
        player.direction = newDirection;
        return (NULL);
    }
}

std::unique_ptr<Player::AState> Player::WalkState::Update(Player &player)
{
    glm::vec2 velocity = glm::normalize(player.direction) * 200.0f * Time::getDeltaTime();
    b2Body_SetLinearVelocity(player.body.GetBodyId(), {velocity.x, velocity.y});

    std::string directionString = "";
    if (player.direction.y < 0)
        directionString = "Up";
    else if (player.direction.y > 0)
        directionString = "Down";
    else
        directionString = "Side";

    player.bodyAnimator.Play("walk" + directionString);

    return (NULL);
}