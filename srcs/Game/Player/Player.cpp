#include "Game/Player/Player.hpp"
#include "Game/PlayerTools/Sword/Sword.hpp"
#include "Game/PlayerTools/Pickaxe/Pickaxe.hpp"
#include "Game/CategoriesFilter.hpp"
#include "Engine/Renderers/SpriteRenderer/SpriteRenderer.hpp"
#include "Engine/WindowManager/WindowManager.hpp"
#include "Engine/Time/Time.hpp"
#include "globals.hpp"
#include <iostream>
#include "Game/Player/PlayerStates/IdleWalkState/IdleWalkState.hpp"

Player::Player()
{
}

Player::~Player()
{
}

void Player::Init(b2WorldId worldId)
{
    glm::vec2 position = glm::vec2(WindowManager::GetWindowWidth() * 0.4, WindowManager::GetWindowHeight() * 0.5);
    direction = glm::vec2(0, 1);
    size = glm::vec2(SPRITE_SIZE, SPRITE_SIZE);
    body = PhysicBody::BodyBuilder().SetPosition(position).SetFixedRotation(true).SetType(b2_dynamicBody).Build(worldId);
        
    b2Filter filter;
    filter.categoryBits = CategoriesFilter::Entities;
    filter.maskBits = CategoriesFilter::Wall;
    body.AddShape("body", PhysicBody::ShapeBuilder().SetFilter(filter).Build(), PhysicBody::PolygonBuilder::Build(size));
    body.AddShape("sword", PhysicBody::ShapeBuilder().IsSensor(true).Build(), PhysicBody::PolygonBuilder::Build(SWORD_HITBOX_SIZE));
    
    state = std::make_unique<IdleWalkState>();
    tool = NULL;
    InitAnimations();
}

void Player::InitAnimations()
{
    {
        Animation idleDownAnimation(0.2);
        for (int i = 0; i < 6; i++)
        {
            Sprite sprite;
            sprite.textureName = "player_idle_run_death";
            sprite.textureSize = glm::vec2(8, 13);
            sprite.spriteCoords = glm::vec2(i, 0);
            idleDownAnimation.AddFrame(sprite);
        }
        
        bodyAnimator.AddAnimation("idleDown", idleDownAnimation);
    }

    {
        Animation idleSideAnimation(0.2);
        for (int i = 0; i < 6; i++)
        {
            Sprite sprite;
            sprite.textureName = "player_idle_run_death";
            sprite.textureSize = glm::vec2(8, 13);
            sprite.spriteCoords = glm::vec2(i, 1);
            idleSideAnimation.AddFrame(sprite);
        }
        
        bodyAnimator.AddAnimation("idleSide", idleSideAnimation);
    }

    {
        Animation idleUpAnimation(0.2);
        for (int i = 0; i < 6; i++)
        {
            Sprite sprite;
            sprite.textureName = "player_idle_run_death";
            sprite.textureSize = glm::vec2(8, 13);
            sprite.spriteCoords = glm::vec2(i, 2);
            idleUpAnimation.AddFrame(sprite);
        }
        
        bodyAnimator.AddAnimation("idleUp", idleUpAnimation);
    }

    {
        Animation walkDownAnimation(0.2);
        for (int i = 0; i < 6; i++)
        {
            Sprite sprite;
            sprite.textureName = "player_idle_run_death";
            sprite.textureSize = glm::vec2(8, 13);
            sprite.spriteCoords = glm::vec2(i, 3);
            walkDownAnimation.AddFrame(sprite);
        }
        
        bodyAnimator.AddAnimation("walkDown", walkDownAnimation);
    }

    {
        Animation walkSideAnimation(0.2);
        for (int i = 0; i < 6; i++)
        {
            Sprite sprite;
            sprite.textureName = "player_idle_run_death";
            sprite.textureSize = glm::vec2(8, 13);
            sprite.spriteCoords = glm::vec2(i, 4);
            walkSideAnimation.AddFrame(sprite);
        }
        
        bodyAnimator.AddAnimation("walkSide", walkSideAnimation);
    }
    
    {
        Animation walkUpAnimation(0.2);
        for (int i = 0; i < 6; i++)
        {
            Sprite sprite;
            sprite.textureName = "player_idle_run_death";
            sprite.textureSize = glm::vec2(8, 13);
            sprite.spriteCoords = glm::vec2(i, 5);
            walkUpAnimation.AddFrame(sprite);
        }
        
        bodyAnimator.AddAnimation("walkUp", walkUpAnimation);
    }

    {
        Animation attackAnimation(0.2, false);
        for (int i = 0; i < 4; i++)
        {
            Sprite sprite;
            sprite.textureName = "player_attack";
            sprite.textureSize = glm::vec2(4, 9);
            sprite.spriteCoords = glm::vec2(i, 0);
            attackAnimation.AddFrame(sprite);
        }
        
        bodyAnimator.AddAnimation("attack1Down", attackAnimation);
    }

    {
        Animation attackAnimation(0.2, false);
        for (int i = 0; i < 4; i++)
        {
            Sprite sprite;
            sprite.textureName = "player_attack";
            sprite.textureSize = glm::vec2(4, 9);
            sprite.spriteCoords = glm::vec2(i, 4);
            attackAnimation.AddFrame(sprite);
        }
        
        bodyAnimator.AddAnimation("attack1Side", attackAnimation);
    }

    {
        Animation attackAnimation(0.2, false);
        for (int i = 0; i < 4; i++)
        {
            Sprite sprite;
            sprite.textureName = "player_attack";
            sprite.textureSize = glm::vec2(4, 9);
            sprite.spriteCoords = glm::vec2(i, 7);
            attackAnimation.AddFrame(sprite);
        }
        
        bodyAnimator.AddAnimation("attack1Up", attackAnimation);
    }

    {
        Animation miningAnimation(0.2, false);
        for (int i = 0; i < 6; i++)
        {
            Sprite sprite;
            sprite.textureName = "player_actions";
            sprite.textureSize = glm::vec2(6, 12);
            sprite.spriteCoords = glm::vec2(i, 0);
            miningAnimation.AddFrame(sprite);
        }
        
        bodyAnimator.AddAnimation("miningSide", miningAnimation);
    }

    {
        Animation miningAnimation(0.2, false);
        for (int i = 0; i < 6; i++)
        {
            Sprite sprite;
            sprite.textureName = "player_actions";
            sprite.textureSize = glm::vec2(6, 12);
            sprite.spriteCoords = glm::vec2(i, 1);
            miningAnimation.AddFrame(sprite);
        }
        
        bodyAnimator.AddAnimation("miningDown", miningAnimation);
    }

    {
        Animation miningAnimation(0.2, false);
        for (int i = 0; i < 6; i++)
        {
            Sprite sprite;
            sprite.textureName = "player_actions";
            sprite.textureSize = glm::vec2(6, 12);
            sprite.spriteCoords = glm::vec2(i, 2);
            miningAnimation.AddFrame(sprite);
        }
        
        bodyAnimator.AddAnimation("miningUp", miningAnimation);
    }

    {
        Animation attackAnimation(0.2, false);
        for (int i = 0; i < 4; i++)
        {
            Sprite sprite;
            sprite.textureName = "iron_sword";
            sprite.textureSize = glm::vec2(6, 9);
            sprite.spriteCoords = glm::vec2(i, 0);
            attackAnimation.AddFrame(sprite);
        }
        
        toolAnimator.AddAnimation("iron_sword_attack1Down", attackAnimation);
    }

    {
        Animation attackAnimation(0.2, false);
        for (int i = 0; i < 4; i++)
        {
            Sprite sprite;
            sprite.textureName = "iron_sword";
            sprite.textureSize = glm::vec2(6, 9);
            sprite.spriteCoords = glm::vec2(i, 4);
            attackAnimation.AddFrame(sprite);
        }
        
        toolAnimator.AddAnimation("iron_sword_attack1Side", attackAnimation);
    }

    {
        Animation attackAnimation(0.2, false);
        for (int i = 0; i < 4; i++)
        {
            Sprite sprite;
            sprite.textureName = "iron_sword";
            sprite.textureSize = glm::vec2(6, 9);
            sprite.spriteCoords = glm::vec2(i, 7);
            attackAnimation.AddFrame(sprite);
        }
        
        toolAnimator.AddAnimation("iron_sword_attack1Up", attackAnimation);
    }

    {
        Animation miningAnimation(0.2, false);
        for (int i = 0; i < 6; i++)
        {
            Sprite sprite;
            sprite.textureName = "iron_tools";
            sprite.textureSize = glm::vec2(6, 12);
            sprite.spriteCoords = glm::vec2(i, 0);
            miningAnimation.AddFrame(sprite);
        }
        
        toolAnimator.AddAnimation("iron_pickaxeSide", miningAnimation);
    }

    {
        Animation miningAnimation(0.2, false);
        for (int i = 0; i < 6; i++)
        {
            Sprite sprite;
            sprite.textureName = "iron_tools";
            sprite.textureSize = glm::vec2(6, 12);
            sprite.spriteCoords = glm::vec2(i, 1);
            miningAnimation.AddFrame(sprite);
        }
        
        toolAnimator.AddAnimation("iron_pickaxeDown", miningAnimation);
    }

    {
        Animation miningAnimation(0.2, false);
        for (int i = 0; i < 6; i++)
        {
            Sprite sprite;
            sprite.textureName = "iron_tools";
            sprite.textureSize = glm::vec2(6, 12);
            sprite.spriteCoords = glm::vec2(i, 2);
            miningAnimation.AddFrame(sprite);
        }
        
        toolAnimator.AddAnimation("iron_pickaxeUp", miningAnimation);
    }


    bodyAnimator.Play("walkDown");
    toolAnimator.Play("none");
}

void Player::Update()
{
    bodyAnimator.Update();
    toolAnimator.Update();

    if (WindowManager::IsKeyPressed(GLFW_KEY_1))
        tool = NULL;
    else if (WindowManager::IsKeyPressed(GLFW_KEY_2))
        tool = std::make_unique<Sword>();
    else if (WindowManager::IsKeyPressed(GLFW_KEY_3))
        tool = std::make_unique<Pickaxe>();

    auto ptr = state->Input(*this);
    if (ptr)
    {
        state->Exit(*this);
        state = std::move(ptr);
        state->Enter(*this);
    }
    ptr = state->Update(*this);
    if (ptr)
    {
        state->Exit(*this);
        state = std::move(ptr);
        state->Enter(*this);
    }
}

void Player::Draw()
{
    bool flipHorizontally;
    if (direction.x < 0)
            flipHorizontally = true;
        else
            flipHorizontally = false;
    
    SpriteRenderer::Draw(body.GetPosition(), size * 1.5f, body.GetAngle(), glm::vec3(1, 1, 1), bodyAnimator.GetFrame(), flipHorizontally, false, 1);
    if (toolAnimator.GetCurrentAnimation() != "none")
        SpriteRenderer::Draw(body.GetPosition(), size * 1.5f, body.GetAngle(), glm::vec3(1, 1, 1), toolAnimator.GetFrame(), flipHorizontally, false, 1);
}


glm::vec2 Player::GetPosition() const
{
    return (body.GetPosition());
}


std::string Player::DetermineDirectionString() const
{
    if (direction.y < 0)
        return ("Up");
    else if (direction.y > 0)
        return ("Down");
    else
        return ("Side");
}
