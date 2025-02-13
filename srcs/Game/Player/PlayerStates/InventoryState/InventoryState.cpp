#include "Game/Player/PlayerStates/InventoryState/InventoryState.hpp"
#include "Game/Player/PlayerStates/IdleWalkState/IdleWalkState.hpp"
#include "Game/CategoriesFilter.hpp"
#include "Engine/WindowManager/WindowManager.hpp"
#include <iostream>

Player::InventoryState::InventoryState(): Player::AState(Player::StateType::INVENTORY)
{
}

Player::InventoryState::~InventoryState()
{
}

void Player::InventoryState::Enter(Player &player)
{
    player.bodyAnimationManager.Play("idle_" + player.DetermineDirectionString());
    b2Body_SetLinearVelocity(player.body.GetBodyId(), {0, 0});
    player.inventoryUI.SetOpen(true);
}

std::unique_ptr<Player::AState> Player::InventoryState::Input(Player &player)
{
    (void)player;
    if (WindowManager::IsInputPressed(GLFW_KEY_E))
        return (std::make_unique<Player::IdleWalkState>());

    return (NULL);
}

void Player::InventoryState::Exit(Player &player)
{
    player.inventoryUI.SetOpen(false);
}