#pragma once

#include "Game/Player/Player.hpp"

class Player::InventoryState: public Player::AState
{
    public:
        InventoryState();
        ~InventoryState();

        void Enter(Player &player);
        std::unique_ptr<Player::AState> Input(Player &player);
        void Exit(Player &player);
};