#include "Game/Player/Player.hpp"
#include "Game/CategoriesFilter.hpp"
#include "Engine/Renderers/SpriteRenderer/SpriteRenderer.hpp"
#include "globals.hpp"
#include "Engine/WindowManager/WindowManager.hpp"
Player::Player()
{
    {
        Animation walkDownAnimation;
        walkDownAnimation.SetAnimationSpeed(0.2);
        for (int i = 0; i < 6; i++)
        {
            Sprite sprite;
            sprite.textureName = "player";
            sprite.textureSize = glm::vec2(6, 10);
            sprite.spriteCoords = glm::vec2(i, 3);
            walkDownAnimation.AddFrame(sprite);
        }
        
        animator.AddAnimation("walkDown", walkDownAnimation);
    }

    {
        Animation walkSideAnimation;
        walkSideAnimation.SetAnimationSpeed(0.2);
        for (int i = 0; i < 6; i++)
        {
            Sprite sprite;
            sprite.textureName = "player";
            sprite.textureSize = glm::vec2(6, 10);
            sprite.spriteCoords = glm::vec2(i, 4);
            walkSideAnimation.AddFrame(sprite);
        }
        
        animator.AddAnimation("walkSide", walkSideAnimation);
    }
    
    {
        Animation walkUpAnimation;
        walkUpAnimation.SetAnimationSpeed(0.2);
        for (int i = 0; i < 6; i++)
        {
            Sprite sprite;
            sprite.textureName = "player";
            sprite.textureSize = glm::vec2(6, 10);
            sprite.spriteCoords = glm::vec2(i, 5);
            walkUpAnimation.AddFrame(sprite);
        }
        
        animator.AddAnimation("walkUp", walkUpAnimation);
    }

    {
        Animation attackAnimation;
        attackAnimation.SetAnimationSpeed(0.2);
        for (int i = 0; i < 4; i++)
        {
            Sprite sprite;
            sprite.textureName = "player";
            sprite.textureSize = glm::vec2(6, 10);
            sprite.spriteCoords = glm::vec2(i, 6);
            attackAnimation.AddFrame(sprite);
        }
        
        animator.AddAnimation("attack", attackAnimation);
    }

    animator.Play("walkDown");
}

Player::~Player()
{

}

void Player::Draw()
{
    bool flipHorizontally = false;
    b2Vec2 velocity = b2Body_GetLinearVelocity(body.GetBodyId());
    if (velocity.x == 0)
    {
        if (velocity.y < 0)
            animator.Play("walkUp");
        else
            animator.Play("walkDown");
    }
    else
    {
        animator.Play("walkSide");
        if (velocity.x < 0)
            flipHorizontally = true;
    }


    if (WindowManager::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_2))
        animator.Play("attack");

    animator.Update();
    SpriteRenderer::Draw(body.GetPosition(), size * 1.5f, body.GetAngle(), glm::vec3(1, 1, 1), animator.GetFrame(), flipHorizontally, false);
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

