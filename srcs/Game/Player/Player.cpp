#include "Game/Player/Player.hpp"
#include "Game/Player/PlayerTools/Sword/Sword.hpp"
#include "Game/Player/PlayerTools/Pickaxe/Pickaxe.hpp"
#include "Game/Player/PlayerTools/Axe/Axe.hpp"
#include "Game/Player/PlayerTools/Hoe/Hoe.hpp"
#include "Game/Player/PlayerTools/WateringCan/WateringCan.hpp"
#include "Game/CategoriesFilter.hpp"
#include "Engine/Renderers/SpriteRenderer/SpriteRenderer.hpp"
#include "Engine/WindowManager/WindowManager.hpp"
#include "Engine/RessourceManager/RessourceManager.hpp"
#include "Engine/Time/Time.hpp"
#include "globals.hpp"
#include <iostream>
#include "Game/Player/PlayerStates/IdleWalkState/IdleWalkState.hpp"
#include <fstream>
#include <nlohmann/json.hpp>

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
    std::ifstream input("saves/animations.json");
    nlohmann::json file =  nlohmann::json::parse(input);

    auto itTextures = file.find("textures"); //@todo error check
    for (auto it : *itTextures)
    {
        RessourceManager::AddTexture(it["name"], it["path"]);
    }

    auto itAnimations = file.find("animations");
    auto itPlayerAnimations = itAnimations->find("player");
    for (auto it = itPlayerAnimations->begin(); it != itPlayerAnimations->end(); ++it)
    {
        Animation animation;

        auto itFrames = it->find("frames");
        for (auto itFrame : *itFrames)
        {
            Sprite newFrame;
            newFrame.textureName = itFrame["texture"]["name"];
            newFrame.textureSize = {itFrame["texture"]["size"][0], itFrame["texture"]["size"][1]};
            newFrame.spriteCoords = {itFrame["position"][0], itFrame["position"][1]};
            animation.AddFrame(newFrame);
        }
        animation.SetStoppable((*it)["stoppable"]);
        
        bodyAnimationManager.AddAnimation(it.key(), animation);
    }

    auto itToolsAnimations = itAnimations->find("tools");
    for (auto it = itToolsAnimations->begin(); it != itToolsAnimations->end(); ++it)
    {
        Animation animation;

        auto itFrames = it->find("frames");
        for (auto itFrame : *itFrames)
        {
            Sprite newFrame;
            newFrame.textureName = itFrame["texture"]["name"];
            newFrame.textureSize = {itFrame["texture"]["size"][0], itFrame["texture"]["size"][1]};
            newFrame.spriteCoords = {itFrame["position"][0], itFrame["position"][1]};
            animation.AddFrame(newFrame);
        }
        animation.SetStoppable((*it)["stoppable"]);
        
        toolAnimationManager.AddAnimation(it.key(), animation);
    }

    auto itWeaponsAnimations = itAnimations->find("weapons");
    for (auto it = itWeaponsAnimations->begin(); it != itWeaponsAnimations->end(); ++it)
    {
        Animation animation;

        auto itFrames = it->find("frames");
        for (auto itFrame : *itFrames)
        {
            Sprite newFrame;
            newFrame.textureName = itFrame["texture"]["name"];
            newFrame.textureSize = {itFrame["texture"]["size"][0], itFrame["texture"]["size"][1]};
            newFrame.spriteCoords = {itFrame["position"][0], itFrame["position"][1]};
            animation.AddFrame(newFrame);
        }
        animation.SetStoppable((*it)["stoppable"]);
        
        toolAnimationManager.AddAnimation(it.key(), animation);
    }

    bodyAnimationManager.Play("idle_down");
    toolAnimationManager.Play("none");
}

void Player::Update()
{
    bodyAnimationManager.Update();
    toolAnimationManager.Update();

    if (WindowManager::IsKeyPressed(GLFW_KEY_1))
    {
        tool = NULL;
        inventoryUI.SetSlotSelected(0);
    }
    else if (WindowManager::IsKeyPressed(GLFW_KEY_2))
    {
        tool = std::make_unique<Sword>();
        inventoryUI.SetSlotSelected(1);
    }
    else if (WindowManager::IsKeyPressed(GLFW_KEY_3))
    {
        tool = std::make_unique<Pickaxe>();
        inventoryUI.SetSlotSelected(2);
    }
    else if (WindowManager::IsKeyPressed(GLFW_KEY_4))
    {
        tool = std::make_unique<Axe>();
        inventoryUI.SetSlotSelected(3);
    }
    else if (WindowManager::IsKeyPressed(GLFW_KEY_5))
    {
        tool = std::make_unique<Hoe>();
        inventoryUI.SetSlotSelected(4);
    }
    else if (WindowManager::IsKeyPressed(GLFW_KEY_6))
    {
        tool = std::make_unique<WateringCan>();
        inventoryUI.SetSlotSelected(5);
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
    if (state->GetStateType() == StateType::MINING || state->GetStateType() == StateType::CHOPPING || state->GetStateType() == StateType::PLOWING || state->GetStateType() == StateType::WATERING) // @todo does a bit mask could work ?
        scale = scale * 1.5f;
    SpriteRenderer::Draw(body.GetPosition(), size * scale, body.GetAngle(), glm::vec3(1, 1, 1), bodyAnimationManager.GetFrame(), flipHorizontally, false, 1);
    if (toolAnimationManager.GetCurrentAnimation() != "none")
        SpriteRenderer::Draw(body.GetPosition(), size * scale, body.GetAngle(), glm::vec3(1, 1, 1), toolAnimationManager.GetFrame(), flipHorizontally, false, 1);

    inventoryUI.Draw(*this);
}


glm::vec2 Player::GetPosition() const
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
