#pragma once

#include "Game/Player/Player.hpp"

class Player::ChoppingState: public Player::AState
{
    public:
        ChoppingState();
        ~ChoppingState();

        void Enter(Player &player);
        std::unique_ptr<Player::AState> Update(Player &player);
};