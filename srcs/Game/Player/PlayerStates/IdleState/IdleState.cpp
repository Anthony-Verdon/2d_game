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

std::unique_ptr<Player::AState> Player::IdleState::Input()
{
    glm::vec2 velocity;
    velocity.x = WindowManager::IsKeyPressed(GLFW_KEY_D) - WindowManager::IsKeyPressed(GLFW_KEY_A);
    velocity.y = WindowManager::IsKeyPressed(GLFW_KEY_S) - WindowManager::IsKeyPressed(GLFW_KEY_W);
    if (velocity != glm::vec2(0, 0))
        return (std::make_unique<Player::WalkState>());
    else
        return (NULL);
}

std::unique_ptr<Player::AState> Player::IdleState::Update()
{
    std::cout << "play idle animation" << std::endl;
    return (NULL);
}