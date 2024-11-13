#include "Game/Player/Player.hpp"
#include "Engine/Renderers/SpriteRenderer/SpriteRenderer.hpp"
#include "globals.hpp"

Player::Player()
{
    animator.SetAnimationSpeed(0.2);
    animator.AddFrame(glm::vec2(0, 7));
    animator.AddFrame(glm::vec2(1, 7));
    animator.AddFrame(glm::vec2(2, 7));
    animator.AddFrame(glm::vec2(3, 7));
    animator.AddFrame(glm::vec2(4, 7));
}

Player::~Player()
{

}
void Player::Draw()
{
    animator.Update();
    SpriteRenderer::Draw(body.GetPosition(), size, body.GetAngle(), glm::vec3(1, 1, 1), "TileMapDungeon", glm::vec2(12,11), animator.GetFrame());
}

void Player::Move(const glm::vec2 &amount)
{
    b2Body_SetLinearVelocity(body.GetBodyId(), {amount.x, amount.y});
}

void Player::Init(b2WorldId worldId)
{
    glm::vec2 position = glm::vec2(WINDOW_WIDTH * 0.4, WINDOW_HEIGHT * 0.5);
    size = glm::vec2(SPRITE_SIZE, SPRITE_SIZE);
    body = PhysicBody::Builder().SetPosition(position).SetSize(size).SetType(b2_dynamicBody).SetFixedRotation(true).Build(worldId);
}

glm::vec2 Player::GetPosition() const
{
    return (body.GetPosition());
}

