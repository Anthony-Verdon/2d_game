#include "Game/Player/Player.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "Engine/Time/Time.hpp"
#include <iostream>
#include "Engine/SpriteRenderer/SpriteRenderer.hpp"

Player::Player(): GameObject()
{
    coords = glm::vec2(0, 0);
    speed = 200;

    AddComponent(std::make_unique<SpriteRenderer>("TileMapDungeon", 5.0f * glm::vec2(16, 16), coords, 0, glm::vec3(1, 1, 1), 1, 1, false));
    GetComponent<SpriteRenderer>()->SetSprite(glm::vec2(12,11), glm::vec2(0,7));
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
    {
        coords = coords + glm::normalize(direction) * Time::getDeltaTime() * speed;
        GetComponent<SpriteRenderer>()->SetPosition(coords); //@todo: when modifying coords of the parent, it should automatically modify it for it
    }
        
}

void Player::Draw()
{
    GetComponent<SpriteRenderer>()->Draw();
}