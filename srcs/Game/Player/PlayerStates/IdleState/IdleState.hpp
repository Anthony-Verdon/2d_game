#pragma once

#include "Game/Player/Player.hpp"

class Player::IdleState: public Player::AState
{
    public:
        IdleState();
        ~IdleState();

        std::unique_ptr<Player::AState> Input(Player &player);
        std::unique_ptr<Player::AState> Update(Player &player);
};