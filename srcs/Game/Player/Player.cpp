#include "Game/Player/Player.hpp"
#include "Game/CategoriesFilter.hpp"
#include "Engine/Renderers/SpriteRenderer/SpriteRenderer.hpp"
#include "globals.hpp"
#include "Engine/WindowManager/WindowManager.hpp"
#include "Engine/Time/Time.hpp"
Player::Player()
{
}

Player::~Player()
{
}

void Player::Init(b2WorldId worldId)
{
    glm::vec2 position = glm::vec2(WINDOW_WIDTH * 0.4, WINDOW_HEIGHT * 0.5);
    direction = glm::vec2(0, 1);
    size = glm::vec2(SPRITE_SIZE, SPRITE_SIZE);
    body = PhysicBody::BodyBuilder().SetPosition(position).SetFixedRotation(true).SetType(b2_dynamicBody).Build(worldId);
        
    b2Filter filter;
    filter.categoryBits = CategoriesFilter::Entities;
    filter.maskBits = CategoriesFilter::Wall;
    body.AddShape("body", PhysicBody::ShapeBuilder().SetFilter(filter).Build(), PhysicBody::PolygonBuilder::Build(size));
    body.AddShape("sword", PhysicBody::ShapeBuilder().IsSensor(true).Build(), PhysicBody::PolygonBuilder::Build(SWORD_HITBOX_SIZE));
    
    InitAnimations();
}

void Player::InitAnimations()
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

void Player::Update()
{
    Move();
    UpdateSwordHitbox();
}

void Player::Move()
{
    glm::vec2 velocity;
    velocity.x = WindowManager::IsKeyPressed(GLFW_KEY_D) - WindowManager::IsKeyPressed(GLFW_KEY_A);
    velocity.y = WindowManager::IsKeyPressed(GLFW_KEY_S) - WindowManager::IsKeyPressed(GLFW_KEY_W);
    if (animator.CurrentAnimationEnded() && velocity != glm::vec2(0, 0))
    {
        direction = velocity;
        glm::vec2 movement = glm::normalize(velocity) * 200.0f * Time::getDeltaTime();
        b2Body_SetLinearVelocity(body.GetBodyId(), {movement.x, movement.y});
    }
    else
    {
        b2Body_SetLinearVelocity(body.GetBodyId(),{0, 0});
    }
}   

void Player::UpdateSwordHitbox()
{
    b2ShapeId swordId = body.GetShape("sword");
    b2Polygon swordPolygon;

    if (direction.x == 0)
    {
        if (direction.y < 0)
            swordPolygon = PhysicBody::PolygonBuilder::Build(SWORD_HITBOX_SIZE, glm::vec2(0, -SWORD_HITBOX_OFFSET));
        else
            swordPolygon = PhysicBody::PolygonBuilder::Build(SWORD_HITBOX_SIZE, glm::vec2(0, SWORD_HITBOX_OFFSET));
    }
    else
    {
        if (direction.x < 0)
            swordPolygon = PhysicBody::PolygonBuilder::Build(SWORD_HITBOX_SIZE, glm::vec2(-SWORD_HITBOX_OFFSET, 0));
        else
            swordPolygon = PhysicBody::PolygonBuilder::Build(SWORD_HITBOX_SIZE, glm::vec2(SWORD_HITBOX_OFFSET, 0));
    }

    b2Shape_SetPolygon(swordId, &swordPolygon);
}

void Player::Draw()
{
    animator.Update();
    bool flipHorizontally = false;
    
    if (direction.x == 0)
    {
        if (direction.y < 0)
            animator.Play("walkUp");
        else
            animator.Play("walkDown");
    }
    else
    {
        animator.Play("walkSide");
        if (direction.x < 0)
            flipHorizontally = true;
        else
            flipHorizontally = false;
    }

    if (WindowManager::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_2))
        animator.Play("attack");

    SpriteRenderer::Draw(body.GetPosition(), size * 1.5f, body.GetAngle(), glm::vec3(1, 1, 1), animator.GetFrame(), flipHorizontally, false);
}


glm::vec2 Player::GetPosition() const
{
    return (body.GetPosition());
}

