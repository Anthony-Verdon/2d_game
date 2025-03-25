#include "Game/Barrel/Barrel.hpp"
#include "Game/CategoriesFilter.hpp"
#include "Engine/2D/Renderers/SpriteRenderer/SpriteRenderer.hpp"
#include "globals.hpp"
#include "Engine/WindowManager/WindowManager.hpp"

Barrel::Barrel()
{
}

Barrel::~Barrel()
{

}

void Barrel::Draw()
{
    Sprite sprite;
    sprite.textureName = "chest";
    sprite.textureSize = glm::vec2(6, 1);
    sprite.spriteCoords = glm::vec2(0, 0);
    SpriteRenderer::Draw(body.GetPosition(), size, body.GetAngle(), glm::vec3(1, 1, 1), sprite, false, false, 1);
}

void Barrel::Init(b2WorldId worldId)
{
    glm::vec2 position = WindowManager::GetWindowSize() * 0.5f;
    size = glm::vec2(SPRITE_SIZE, SPRITE_SIZE);
    b2Filter filter;
    filter.categoryBits = CategoriesFilter::Entities;
    filter.maskBits = CategoriesFilter::Wall;

    body = PhysicBody::BodyBuilder().SetPosition(position).SetType(b2_kinematicBody).Build(worldId);
    body.AddShape("body", PhysicBody::ShapeBuilder().Build(), PhysicBody::PolygonBuilder::Build(size));
}