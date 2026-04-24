#include "Game/Skeletton/Skeletton.hpp"
#include "Game/CategoriesFilter.hpp"
#include "Engine/2D/Renderers/SpriteRenderer/SpriteRenderer.hpp"
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
    ml::vec2 position = ml::vec2(WindowManager::GetWindowWidth() * 0.2, WindowManager::GetWindowHeight() * 0.5);
    size = ml::vec2(SPRITE_SIZE, SPRITE_SIZE);
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
        Animation2D idleAnimation(0.2);
        for (int i = 0; i < 6; i++)
        {
            Sprite sprite;
            sprite.textureName = "skeletton_mage";
            sprite.textureSize = ml::vec2(8, 13);
            sprite.spriteCoords = ml::vec2(i, 0);
            idleAnimation.AddFrame(sprite);
        }

        animator.AddAnimation("idleDown", idleAnimation);
    }

    {
        Animation2D hurtAnimation(0.2, false);
        for (int i = 0; i < 4; i++)
        {
            Sprite sprite;
            sprite.textureName = "skeletton_mage";
            sprite.textureSize = ml::vec2(8, 13);
            sprite.spriteCoords = ml::vec2(i, 10);
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
    }
}

void Skeletton::PlayAnimation(const std::string &name)
{
    animator.Play(name);
}

void Skeletton::Draw()
{
    SpriteRenderer::Draw(body.GetPosition(), size * 1.5f, body.GetAngle(), ml::vec3(1, 1, 1), animator.GetFrame(), false, false, 1);
}