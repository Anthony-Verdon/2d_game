#include "Game/Player/Player.hpp"
#include "Game/PlayerTools/Sword/Sword.hpp"
#include "Game/PlayerTools/Pickaxe/Pickaxe.hpp"
#include "Game/CategoriesFilter.hpp"
#include "Engine/Renderers/SpriteRenderer/SpriteRenderer.hpp"
#include "Engine/WindowManager/WindowManager.hpp"
#include "Engine/Time/Time.hpp"
#include "globals.hpp"
#include <iostream>

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
    
    InitAnimations();
}

void Player::InitAnimations()
{
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

    bodyAnimator.Play("walkDown");
    toolAnimator.Play("none");
}

void Player::Update()
{
    if (WindowManager::IsKeyPressed(GLFW_KEY_1))
    {
        std::cout << "tool selected: none" << std::endl;
        tool = NULL;
    }
    else if (WindowManager::IsKeyPressed(GLFW_KEY_2))
    {
        std::cout << "tool selected: sword" << std::endl;
        tool = std::make_unique<Sword>();
    }
    else if (WindowManager::IsKeyPressed(GLFW_KEY_3))
    {
        std::cout << "tool selected: pickaxe" << std::endl;
        tool = std::make_unique<Pickaxe>();
    }

    if (WindowManager::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_1) && tool)
    {
        tool->MainAction();
        switch (tool->GetType())
        {
            case PlayerTool::SWORD:
                state = PlayerState::ATTACK;
            case PlayerTool::PICKAXE:
                state = PlayerState::MINING;
            default:
                break;
        }
    }
    else if (Move()) // movements du personnage
    {
        // run
        // modification du state
        state = PlayerState::RUN;
    }
    else
    {
        state = PlayerState::IDLE;
    }
}

bool Player::Move()
{
    glm::vec2 velocity;
    velocity.x = WindowManager::IsKeyPressed(GLFW_KEY_D) - WindowManager::IsKeyPressed(GLFW_KEY_A);
    velocity.y = WindowManager::IsKeyPressed(GLFW_KEY_S) - WindowManager::IsKeyPressed(GLFW_KEY_W);
    if (bodyAnimator.CurrentAnimationEnded() && velocity != glm::vec2(0, 0))
    {
        direction = velocity;
        glm::vec2 movement = glm::normalize(velocity) * 200.0f * Time::getDeltaTime();
        b2Body_SetLinearVelocity(body.GetBodyId(), {movement.x, movement.y});
        return (true);
    }
    else
    {
        b2Body_SetLinearVelocity(body.GetBodyId(),{0, 0});
        return (false);
    }
}   

void Player::Draw()
{
    bodyAnimator.Update();
    toolAnimator.Update();

    // action
    std::string bodyActionAnimation = "";
    
    bodyActionAnimation = "walk";

    // direction
    std::string directionString = "";
    bool flipHorizontally = false;

    if (direction.x == 0)
    {
        if (direction.y < 0)
            directionString = "Up";
        else
            directionString = "Down";
    }
    else
    {
        directionString = "Side";
        if (direction.x < 0)
            flipHorizontally = true;
        else
            flipHorizontally = false;
    }

    bodyAnimator.Play(bodyActionAnimation + directionString);
    SpriteRenderer::Draw(body.GetPosition(), size * 1.5f, body.GetAngle(), glm::vec3(1, 1, 1), bodyAnimator.GetFrame(), flipHorizontally, false, 1);
}


glm::vec2 Player::GetPosition() const
{
    return (body.GetPosition());
}

