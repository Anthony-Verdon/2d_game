#pragma once

#include "Game/Player/Player.hpp"

class Player::WalkState: public Player::AState
{
    public:
        WalkState();
        ~WalkState();

        std::unique_ptr<Player::AState> Input();
        std::unique_ptr<Player::AState> Update();
};