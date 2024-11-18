#include "Game/Skeletton/Skeletton.hpp"
#include "Game/CategoriesFilter.hpp"
#include "Engine/Renderers/SpriteRenderer/SpriteRenderer.hpp"
#include "Engine/WindowManager/WindowManager.hpp"
#include "Engine/Time/Time.hpp"
#include "globals.hpp"

Skeletton::Skeletton()
{
}

Skeletton::~Skeletton()
{
}

void Skeletton::Init(b2WorldId worldId)
{
    glm::vec2 position = glm::vec2(WindowManager::GetWindowWidth() * 0.2, WindowManager::GetWindowHeight() * 0.5);
    size = glm::vec2(SPRITE_SIZE, SPRITE_SIZE);
    body = PhysicBody::BodyBuilder().SetPosition(position).SetFixedRotation(true).SetType(b2_kinematicBody).Build(worldId);
    
    b2Filter filter = b2DefaultFilter();
    filter.categoryBits = CategoriesFilter::Everything;
    filter.maskBits = CategoriesFilter::Everything;
    body.AddShape("body", PhysicBody::ShapeBuilder().SetUserData(this).SetFilter(filter).Build(), PhysicBody::PolygonBuilder::Build(size));
    
    InitAnimations();
}

void Skeletton::InitAnimations()
{
    {
        Animation idleAnimation(0.2);
        for (int i = 0; i < 6; i++)
        {
            Sprite sprite;
            sprite.textureName = "skeletton_mage";
            sprite.textureSize = glm::vec2(8, 13);
            sprite.spriteCoords = glm::vec2(i, 0);
            idleAnimation.AddFrame(sprite);
        }
        
        animator.AddAnimation("idleDown", idleAnimation);
    }

    {
        Animation hurtAnimation(0.2, false);
        for (int i = 0; i < 4; i++)
        {
            Sprite sprite;
            sprite.textureName = "skeletton_mage";
            sprite.textureSize = glm::vec2(8, 13);
            sprite.spriteCoords = glm::vec2(i, 10);
            hurtAnimation.AddFrame(sprite);
        }
        
        animator.AddAnimation("hurtDown", hurtAnimation);
    }

    animator.Play("idleDown");
}


void Skeletton::Update()
{
    animator.Update(); // should always be update before any other use
    if (animator.CurrentAnimationEnded())
    {
        animator.Play("idleDown");
        b2ShapeId shape = body.GetShape("body");
        b2Filter filter = b2Shape_GetFilter(shape);
        filter.categoryBits = CategoriesFilter::Everything;
        filter.maskBits = CategoriesFilter::Everything;
        b2Shape_SetFilter(shape, filter);
    }
    else
    {
        b2ShapeId shape = body.GetShape("body");
        b2Filter filter = b2Shape_GetFilter(shape);
        filter.categoryBits = CategoriesFilter::Nothing;
        filter.maskBits = CategoriesFilter::Nothing;
        b2Shape_SetFilter(shape, filter);
    }
}

void Skeletton::PlayAnimation(const std::string &name)
{
    animator.Play(name);
}

void Skeletton::Draw()
{
    SpriteRenderer::Draw(body.GetPosition(), size * 1.5f, body.GetAngle(), glm::vec3(1, 1, 1), animator.GetFrame(), false, false);
}