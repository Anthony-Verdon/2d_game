#include "Game/Player/PlayerStates/WalkState/WalkState.hpp"
#include "Game/Player/PlayerStates/IdleState/IdleState.hpp"
#include "Engine/WindowManager/WindowManager.hpp"
#include <iostream>

Player::WalkState::WalkState(): Player::AState()
{
}

Player::WalkState::~WalkState()
{
}

std::unique_ptr<Player::AState> Player::WalkState::Input()
{
    glm::vec2 velocity;

    velocity.x = WindowManager::IsKeyPressed(GLFW_KEY_D) - WindowManager::IsKeyPressed(GLFW_KEY_A);
    velocity.y = WindowManager::IsKeyPressed(GLFW_KEY_S) - WindowManager::IsKeyPressed(GLFW_KEY_W);
    if (velocity == glm::vec2(0, 0))
        return (std::make_unique<Player::IdleState>());
    else
        return (NULL);
}

std::unique_ptr<Player::AState> Player::WalkState::Update()
{
    std::cout << "play walk animation" << std::endl;
    return (NULL);
}