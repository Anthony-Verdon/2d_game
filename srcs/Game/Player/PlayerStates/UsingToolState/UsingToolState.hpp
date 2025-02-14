#pragma once

#include "Game/Player/Player.hpp"

class Player::UsingToolState: public Player::AState
{
    private:
        std::string bodyAnim;
        std::string toolAnim;
        
    public:
        UsingToolState(const std::string &bodyAnim, const std::string &toolAnim);
        ~UsingToolState();

        void Enter(Player &player);
        std::unique_ptr<Player::AState> Update(Player &player);
};