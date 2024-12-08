#pragma once

#include "Game/Player/Player.hpp"

class Player::AttackState: public Player::AState
{
    public:
        AttackState();
        ~AttackState();

        void Enter(Player &player);
        std::unique_ptr<Player::AState> Update(Player &player);
};