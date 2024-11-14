#include "Game/Player/Player.hpp"
#include "Game/CategoriesFilter.hpp"
#include "Engine/Renderers/SpriteRenderer/SpriteRenderer.hpp"
#include "globals.hpp"
#include "Engine/WindowManager/WindowManager.hpp"
Player::Player()
{
    {
        Animation walkDownAnimation(0.2);
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
        Animation walkSideAnimation(0.2);
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
        Animation walkUpAnimation(0.2);
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
        Animation attackAnimation(0.2, false);
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
    animator.Update();

    bool flipHorizontally = false;
    b2Vec2 velocity = b2Body_GetLinearVelocity(body.GetBodyId());
    b2ShapeId swordId = body.GetShape("sword");
    b2Polygon swordPolygon;
    if (velocity.x == 0)
    {
        if (velocity.y < 0)
        {
            animator.Play("walkUp");
            swordPolygon = PhysicBody::PolygonBuilder::Build(SWORD_HITBOX_SIZE, glm::vec2(0, -SWORD_HITBOX_OFFSET));
        }
        else
        {
            animator.Play("walkDown");
            swordPolygon = PhysicBody::PolygonBuilder::Build(SWORD_HITBOX_SIZE, glm::vec2(0, SWORD_HITBOX_OFFSET));
        }
    }
    else
    {
        animator.Play("walkSide");
        if (velocity.x < 0)
        {
            flipHorizontally = true;
            swordPolygon = PhysicBody::PolygonBuilder::Build(SWORD_HITBOX_SIZE, glm::vec2(-SWORD_HITBOX_OFFSET, 0));
        }
        else
        {
            flipHorizontally = false;
            swordPolygon = PhysicBody::PolygonBuilder::Build(SWORD_HITBOX_SIZE, glm::vec2(SWORD_HITBOX_OFFSET, 0));
        }
    }
    b2Shape_SetPolygon(swordId, &swordPolygon);

    if (WindowManager::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_2))
        animator.Play("attack");

    SpriteRenderer::Draw(body.GetPosition(), size * 1.5f, body.GetAngle(), glm::vec3(1, 1, 1), animator.GetFrame(), flipHorizontally, false);
}

void Player::Move(const glm::vec2 &amount)
{
    if (animator.CurrentAnimationEnded())
        b2Body_SetLinearVelocity(body.GetBodyId(), {amount.x, amount.y});
    else
        b2Body_SetLinearVelocity(body.GetBodyId(), {0, 0});

}   

void Player::Init(b2WorldId worldId)
{
    glm::vec2 position = glm::vec2(WINDOW_WIDTH * 0.4, WINDOW_HEIGHT * 0.5);
    size = glm::vec2(SPRITE_SIZE, SPRITE_SIZE);
    
    body = PhysicBody::BodyBuilder().SetPosition(position).SetFixedRotation(true).SetType(b2_dynamicBody).Build(worldId);
        
    b2Filter filter;
    filter.categoryBits = CategoriesFilter::Entities;
    filter.maskBits = CategoriesFilter::Wall;
    body.AddShape("body", PhysicBody::ShapeBuilder().SetFilter(filter).Build(), PhysicBody::PolygonBuilder::Build(size)); // body
    body.AddShape("sword", PhysicBody::ShapeBuilder().IsSensor(true).Build(), PhysicBody::PolygonBuilder::Build(SWORD_HITBOX_SIZE));
}

glm::vec2 Player::GetPosition() const
{
    return (body.GetPosition());
}

