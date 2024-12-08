#include "Game/Player/PlayerStates/IdleState/IdleState.hpp"
#include "Game/Player/PlayerStates/WalkState/WalkState.hpp"
#include "Engine/WindowManager/WindowManager.hpp"
#include <iostream>

Player::IdleState::IdleState(): Player::AState()
{
}

Player::IdleState::~IdleState()
{
}

std::unique_ptr<Player::AState> Player::IdleState::Input(Player &player)
{
    glm::vec2 newDirection;
    newDirection.x = WindowManager::IsKeyPressed(GLFW_KEY_D) - WindowManager::IsKeyPressed(GLFW_KEY_A);
    newDirection.y = WindowManager::IsKeyPressed(GLFW_KEY_S) - WindowManager::IsKeyPressed(GLFW_KEY_W);
    if (newDirection != glm::vec2(0, 0))
    {
        player.direction = newDirection;
        return (std::make_unique<Player::WalkState>());
    }
    else
        return (NULL);
}

std::unique_ptr<Player::AState> Player::IdleState::Update(Player &player)
{
    b2Body_SetLinearVelocity(player.body.GetBodyId(), {0, 0});

    std::string directionString = "";
    if (player.direction.y < 0)
        directionString = "Up";
    else if (player.direction.y > 0)
        directionString = "Down";
    else
        directionString = "Side";

    player.bodyAnimator.Play("idle" + directionString);

    return (NULL);
}