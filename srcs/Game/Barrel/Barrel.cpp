#include "Game/Barrel/Barrel.hpp"
#include "Game/CategoriesFilter.hpp"
#include "Engine/2D/Renderers/SpriteRenderer/SpriteRenderer.hpp"
#include "globals.hpp"
#include "Engine/WindowManager/WindowManager.hpp"
#include "Common/TilemapType.hpp"

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
    sprite.textureSize = ml::vec2(6, 1);
    sprite.spriteCoords = ml::vec2(0, 0);
    SpriteRenderer::Draw(SpriteRenderDataBuilder().SetPosition(ml::vec3(body.GetPosition(), (int)TilemapType::ELEMENTS_AND_CHARACTERS)).SetSize(size).SetSprite(sprite).SetDrawAbsolute(true).Build());
}

void Barrel::Init(b2WorldId worldId)
{
    ml::vec2 position = WindowManager::GetWindowSize() * 0.5f;
    size = ml::vec2(SPRITE_SIZE, SPRITE_SIZE);
    b2Filter filter;
    filter.categoryBits = CategoriesFilter::Entities;
    filter.maskBits = CategoriesFilter::Wall;

    body = PhysicBody::BodyBuilder().SetPosition(position).SetType(b2_kinematicBody).Build(worldId);
    body.AddShape("body", PhysicBody::ShapeBuilder().Build(), PhysicBody::PolygonBuilder::Build(size));
}