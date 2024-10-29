#include "Game/Player/Player.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "Engine/Time/Time.hpp"
#include <iostream>

Player::Player(): SpriteRenderer("TileMapDungeon", glm::vec2(12,11), glm::vec2(0,7), 5.0f * glm::vec2(16, 16), 0, glm::vec3(1, 1, 1))
{
    coords = glm::vec2(0, 0);
    speed = 100;
}

Player::~Player()
{
}

glm::vec2 Player::GetCoords() const
{
    return (coords);
}

void Player::Move(const glm::vec2 &direction)
{
    if (direction != glm::vec2(0, 0))
        coords = coords + glm::normalize(direction) * Time::getDeltaTime() * speed;
        
}

