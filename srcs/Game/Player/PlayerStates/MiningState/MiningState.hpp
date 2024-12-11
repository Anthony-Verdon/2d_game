#pragma once

#include "Game/Player/Player.hpp"

class Player::MiningState: public Player::AState
{
    public:
        MiningState();
        ~MiningState();

        void Enter(Player &player);
        std::unique_ptr<Player::AState> Update(Player &player);
};