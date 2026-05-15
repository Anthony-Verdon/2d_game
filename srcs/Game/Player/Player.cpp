#include "Game/Player/Player.hpp"
#include "Game/Items/ItemBehavior/SwordBehavior/SwordBehavior.hpp"
#include "Game/Items/ItemBehavior/PickaxeBehavior/PickaxeBehavior.hpp"
#include "Game/Items/ItemBehavior/AxeBehavior/AxeBehavior.hpp"
#include "Game/Items/ItemBehavior/HoeBehavior/HoeBehavior.hpp"
#include "Game/Items/ItemBehavior/WateringCanBehavior/WateringCanBehavior.hpp"
#include "Game/CategoriesFilter.hpp"
#include "Engine/2D/Renderers/SpriteRenderer/SpriteRenderer.hpp"
#include "Engine/WindowManager/WindowManager.hpp"
#include "Engine/RessourceManager/RessourceManager.hpp"
#include "Engine/Time/Time.hpp"
#include "globals.hpp"
#include <iostream>
#include "Game/Player/PlayerStates/IdleWalkState/IdleWalkState.hpp"
#include <fstream>
#include "Json/Json.hpp"
#include "Common/TilemapType.hpp"

Player::Player()
{
}

Player::~Player()
{
}

void Player::Init(b2WorldId worldId)
{
    ml::vec2 position = ml::vec2(WindowManager::GetWindowWidth() * 0.4, WindowManager::GetWindowHeight() * 0.5);
    direction = ml::vec2(0, 1);
    size = ml::vec2(SPRITE_SIZE, SPRITE_SIZE);
    body = PhysicBody::BodyBuilder().SetPosition(position).SetFixedRotation(true).SetType(b2_dynamicBody).Build(worldId);

    b2Filter filter;
    filter.categoryBits = CategoriesFilter::Entities;
    filter.maskBits = CategoriesFilter::Wall;
    body.AddShape("body", PhysicBody::ShapeBuilder().SetFilter(filter).Build(), PhysicBody::PolygonBuilder::Build(size));
    body.AddShape("sword", PhysicBody::ShapeBuilder().IsSensor(true).Build(), PhysicBody::PolygonBuilder::Build(SWORD_HITBOX_SIZE));
    state = std::make_unique<IdleWalkState>();
    InitAnimations();
}

void Player::InitAnimations()
{
    Json::Node file = Json::ParseFile(ANIMATION_FILE);

    if (file.KeyExist("textures") && file["textures"] != nullptr)
    {
        for (auto it : file["textures"])
        {
            RessourceManager::AddTexture(it["name"], it["path"]);
        }
    }

    if (file.KeyExist("animations") && file["animations"] != nullptr && file["animations"].KeyExist("player") && file["animations"]["player"] != nullptr)
    {

        Json::Node playerAnim = file["animations"]["player"];
        for (auto it = playerAnim.begin(); it != playerAnim.end(); it++)
        {
            Animation2D animation;

            auto value = it.value();
            for (auto itFrame : value["frames"])
            {
                Sprite newFrame;
                newFrame.textureName = std::string(itFrame["texture"]["name"]);
                newFrame.textureSize = {itFrame["texture"]["size"][0], itFrame["texture"]["size"][1]};
                newFrame.spriteCoords = {itFrame["position"][0], itFrame["position"][1]};
                animation.AddFrame(newFrame);
            }
            animation.SetStoppable(value["stoppable"]);

            bodyAnimationManager.AddAnimation(it.key(), animation);
        }
    }

    if (file.KeyExist("animations") && file["animations"] != nullptr && file["animations"].KeyExist("tools") && file["animations"]["tools"] != nullptr)
    {

        Json::Node toolAnim = file["animations"]["tools"];
        for (auto it = toolAnim.begin(); it != toolAnim.end(); it++)
        {
            Animation2D animation;

            auto value = it.value();
            for (auto itFrame : value["frames"])
            {
                Sprite newFrame;
                newFrame.textureName = std::string(itFrame["texture"]["name"]);
                newFrame.textureSize = {itFrame["texture"]["size"][0], itFrame["texture"]["size"][1]};
                newFrame.spriteCoords = {itFrame["position"][0], itFrame["position"][1]};
                animation.AddFrame(newFrame);
            }
            animation.SetStoppable(value["stoppable"]);

            // @PROBLEM?
            toolAnimationManager.AddAnimation(it.key(), animation);
        }
    }

    if (file.KeyExist("animations") && file["animations"] != nullptr && file["animations"].KeyExist("weapons") && file["animations"]["weapons"] != nullptr)
    {

        Json::Node weaponAnim = file["animations"]["weapons"];
        for (auto it = weaponAnim.begin(); it != weaponAnim.end(); it++)
        {
            Animation2D animation;

            auto value = it.value();
            for (auto itFrame : value["frames"])
            {
                Sprite newFrame;
                newFrame.textureName = std::string(itFrame["texture"]["name"]);
                newFrame.textureSize = {itFrame["texture"]["size"][0], itFrame["texture"]["size"][1]};
                newFrame.spriteCoords = {itFrame["position"][0], itFrame["position"][1]};
                animation.AddFrame(newFrame);
            }
            animation.SetStoppable(value["stoppable"]);

            toolAnimationManager.AddAnimation(it.key(), animation);
        }
    }

    bodyAnimationManager.Play("idle_down");
    toolAnimationManager.Play("none");
}

void Player::Update()
{
    bodyAnimationManager.Update();
    toolAnimationManager.Update();

    for (size_t i = 0; i < 6; i++)
    {
        if (WindowManager::IsInputPressed(GLFW_KEY_1 + i))
            inventoryUI.SetSlotSelected(i);
    }

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

    float scale = 1.5f;
    if (state->GetStateType() == StateType::USING_TOOL)
        scale = scale * 1.5f;
    SpriteRenderer::Draw(SpriteRenderDataBuilder().SetPosition(ml::vec3(body.GetPosition(), (int)TilemapType::ELEMENTS_AND_CHARACTERS)).SetBoundingBox(ml::vec2(50, 50)).SetSize(size * scale).SetSprite(bodyAnimationManager.GetFrame()).SetDrawAbsolute(true).FlipHorizontally(flipHorizontally).Build());
    if (toolAnimationManager.GetCurrentAnimation() != "none")
        SpriteRenderer::Draw(SpriteRenderDataBuilder().SetPosition(ml::vec3(body.GetPosition(), (int)TilemapType::ELEMENTS_AND_CHARACTERS)).SetBoundingBox(ml::vec2(50, 50)).SetSize(size * scale).SetSprite(toolAnimationManager.GetFrame()).SetDrawAbsolute(true).FlipHorizontally(flipHorizontally).Build());

    inventoryUI.Draw(*this);
}

ml::vec2 Player::GetPosition() const
{
    return (body.GetPosition());
}

std::string Player::DetermineDirectionString() const
{
    if (direction.y < 0)
        return ("up");
    else if (direction.y > 0)
        return ("down");
    else
        return ("side");
}
