#pragma once

#include "Game/Player/Player.hpp"

class Player::PlowingState: public Player::AState
{
    public:
        PlowingState();
        ~PlowingState();

        void Enter(Player &player);
        std::unique_ptr<Player::AState> Update(Player &player);
};