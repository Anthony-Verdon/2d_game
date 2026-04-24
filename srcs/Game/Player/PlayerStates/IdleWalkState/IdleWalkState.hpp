#pragma once

#include "Game/Player/Player.hpp"

class Player::IdleWalkState : public Player::AState
{
  private:
    ml::vec2 velocity;

  public:
    IdleWalkState();
    ~IdleWalkState();

    void Enter(Player &player);
    std::unique_ptr<Player::AState> Input(Player &player);
    std::unique_ptr<Player::AState> Update(Player &player);
};