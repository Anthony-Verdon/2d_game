#include "Game/Player/Player.hpp"
#include "Game/CategoriesFilter.hpp"
#include "Engine/Renderers/SpriteRenderer/SpriteRenderer.hpp"
#include "globals.hpp"

Player::Player()
{
    animator.SetAnimationSpeed(0.2);
    for (int i = 0; i < 6; i++)
        animator.AddFrame(glm::vec2(i, 3));
}

Player::~Player()
{

}
void Player::Draw()
{
    animator.Update();
    SpriteRenderer::Draw(body.GetPosition(), size * 1.5f, body.GetAngle(), glm::vec3(1, 1, 1), "player", glm::vec2(6, 10), animator.GetFrame());
}

void Player::Move(const glm::vec2 &amount)
{
    b2Body_SetLinearVelocity(body.GetBodyId(), {amount.x, amount.y});
}

void Player::Init(b2WorldId worldId)
{
    glm::vec2 position = glm::vec2(WINDOW_WIDTH * 0.4, WINDOW_HEIGHT * 0.5);
    size = glm::vec2(SPRITE_SIZE, SPRITE_SIZE);
    b2Filter filter;
    filter.categoryBits = CategoriesFilter::Entities;
    filter.maskBits = CategoriesFilter::Wall;
    body = PhysicBody::Builder().SetPosition(position).SetSize(size).SetType(b2_dynamicBody).SetFixedRotation(true).SetFilter(filter).Build(worldId);
}

glm::vec2 Player::GetPosition() const
{
    return (body.GetPosition());
}

