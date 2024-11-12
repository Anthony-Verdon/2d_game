#include "Game/Player/Player.hpp"
#include "Engine/Renderers/SpriteRenderer/SpriteRenderer.hpp"
#include "globals.hpp"

Player::Player()
{
}

Player::~Player()
{

}
void Player::Draw()
{
    SpriteRenderer::Draw(body.GetPosition(), size, body.GetAngle(), glm::vec3(1, 1, 1), "TileMapDungeon", glm::vec2(12,11), glm::vec2(0, 7));
}

void Player::Move(const glm::vec2 &amount)
{
    b2Body_SetLinearVelocity(body.GetBodyId(), {amount.x, amount.y});
}

void Player::Init(b2WorldId worldId)
{
    glm::vec2 position = glm::vec2(WINDOW_WIDTH * 0.4, WINDOW_HEIGHT * 0.5);
    size = glm::vec2(64, 64);
    body = PhysicBody::Builder().SetPosition(position).SetSize(size).SetType(b2_dynamicBody).SetFixedRotation(true).Build(worldId);
}


