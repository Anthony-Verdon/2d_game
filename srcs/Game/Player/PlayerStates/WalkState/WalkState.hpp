#pragma once

#include "Game/Player/Player.hpp"

class Player::WalkState: public Player::AState
{
    public:
        WalkState();
        ~WalkState();

        void Enter(Player &player);
        std::unique_ptr<Player::AState> Input(Player &player);
        std::unique_ptr<Player::AState> Update(Player &player);
};