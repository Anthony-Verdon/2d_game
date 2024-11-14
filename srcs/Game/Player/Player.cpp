#include "Game/Player/Player.hpp"
#include "Game/CategoriesFilter.hpp"
#include "Engine/Renderers/SpriteRenderer/SpriteRenderer.hpp"
#include "globals.hpp"

Player::Player()
{
    Animation walkDownAnimation;
    walkDownAnimation.SetAnimationSpeed(0.2);
    for (int i = 0; i < 6; i++)
    {
        Sprite sprite;
        sprite.textureName = "player";
        sprite.textureSize = glm::vec2(6, 13);
        sprite.spriteCoords = glm::vec2(i, 4);
        walkDownAnimation.AddFrame(sprite);
    }
    
    animator.AddAnimation("walkDown", walkDownAnimation);

    Animation walkRightAnimation;
    walkRightAnimation.SetAnimationSpeed(0.2);
    for (int i = 0; i < 6; i++)
    {
        Sprite sprite;
        sprite.textureName = "player";
        sprite.textureSize = glm::vec2(6, 13);
        sprite.spriteCoords = glm::vec2(i, 5);
        walkRightAnimation.AddFrame(sprite);
    }
    
    animator.AddAnimation("walkRight", walkRightAnimation);

    Animation walkLeftAnimation;
    walkLeftAnimation.SetAnimationSpeed(0.2);
    for (int i = 0; i < 6; i++)
    {
        Sprite sprite;
        sprite.textureName = "player";
        sprite.textureSize = glm::vec2(6, 13);
        sprite.spriteCoords = glm::vec2(i, 6);
        walkLeftAnimation.AddFrame(sprite);
    }
    
    animator.AddAnimation("walkLeft", walkLeftAnimation);

    Animation walkUpAnimation;
    walkUpAnimation.SetAnimationSpeed(0.2);
    for (int i = 0; i < 6; i++)
    {
        Sprite sprite;
        sprite.textureName = "player";
        sprite.textureSize = glm::vec2(6, 13);
        sprite.spriteCoords = glm::vec2(i, 7);
        walkUpAnimation.AddFrame(sprite);
    }
    
    animator.AddAnimation("walkUp", walkUpAnimation);

    animator.Play("walkDown");
}

Player::~Player()
{

}
void Player::Draw()
{
    animator.Update();
    SpriteRenderer::Draw(body.GetPosition(), size * 1.5f, body.GetAngle(), glm::vec3(1, 1, 1), animator.GetFrame());
}

void Player::Move(const glm::vec2 &amount)
{
    if (amount.x == 0)
    {
        if (amount.y < 0)
            animator.Play("walkUp");
        else
            animator.Play("walkDown");
    }
    else
    {
        if (amount.x < 0)
            animator.Play("walkLeft");
        else
            animator.Play("walkRight");
    }

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

