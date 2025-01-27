#pragma once

#include "Game/Player/Player.hpp"

class Player::WateringState: public Player::AState
{
    public:
        WateringState();
        ~WateringState();

        void Enter(Player &player);
        std::unique_ptr<Player::AState> Update(Player &player);
};