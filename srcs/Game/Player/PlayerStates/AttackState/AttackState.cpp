#include "Game/Player/PlayerStates/AttackState/AttackState.hpp"
#include "Game/Player/PlayerStates/IdleWalkState/IdleWalkState.hpp"
#include "Game/CategoriesFilter.hpp"
#include "Engine/WindowManager/WindowManager.hpp"
#include <iostream>

Player::AttackState::AttackState(): Player::AState(Player::StateType::ATTACK)
{
}

Player::AttackState::~AttackState()
{
}

void Player::AttackState::Enter(Player &player)
{
    player.bodyAnimationManager.Play("attack_1_" + player.DetermineDirectionString());
    player.toolAnimationManager.Play("sword_1_" + player.DetermineDirectionString());
    b2Body_SetLinearVelocity(player.body.GetBodyId(), {0, 0});

    b2ShapeId swordId = player.body.GetShape("sword");
    b2Filter filter = b2Shape_GetFilter(swordId);
    filter.categoryBits = CategoriesFilter::Everything;
    filter.maskBits = CategoriesFilter::Everything;
    b2Shape_SetFilter(swordId, filter);

    b2Polygon swordPolygon;
    if (player.direction.x == 0)
    {
        if (player.direction.y < 0)
            swordPolygon = PhysicBody::PolygonBuilder::Build(glm::vec2(SWORD_HITBOX_SIZE.y, SWORD_HITBOX_SIZE.x), glm::vec2(0, -SWORD_HITBOX_OFFSET));
        else
            swordPolygon = PhysicBody::PolygonBuilder::Build(glm::vec2(SWORD_HITBOX_SIZE.y, SWORD_HITBOX_SIZE.x), glm::vec2(0, SWORD_HITBOX_OFFSET));
    }
    else
    {
        if (player.direction.x < 0)
            swordPolygon = PhysicBody::PolygonBuilder::Build(SWORD_HITBOX_SIZE, glm::vec2(-SWORD_HITBOX_OFFSET, 0));
        else
            swordPolygon = PhysicBody::PolygonBuilder::Build(SWORD_HITBOX_SIZE, glm::vec2(SWORD_HITBOX_OFFSET, 0));
    }
    b2Shape_SetPolygon(swordId, &swordPolygon);
}

std::unique_ptr<Player::AState> Player::AttackState::Update(Player &player)
{
    if (!player.bodyAnimationManager.CurrentAnimationEnded())
        return (NULL);
    
    player.toolAnimationManager.Play("none");
    return (std::make_unique<Player::IdleWalkState>());
}

void Player::AttackState::Exit(Player &player)
{
    b2ShapeId swordId = player.body.GetShape("sword");
    b2Filter filter = b2Shape_GetFilter(swordId);
    filter.categoryBits = CategoriesFilter::Nothing;
    filter.maskBits = CategoriesFilter::Nothing;
    b2Shape_SetFilter(swordId, filter);
}