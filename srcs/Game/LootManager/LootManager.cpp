#include "Game/LootManager/LootManager.hpp"
#include "Engine/Renderers/SpriteRenderer/SpriteRenderer.hpp"
#include <cmath>
#include "globals.hpp"

std::vector<Loot> LootManager::loots;

void LootManager::AddLoot(const Loot &loot)
{
    loots.push_back(loot);
}

void LootManager::UpdateLoot(const glm::vec2 &playerPos)
{
    for (auto it = loots.begin(); it != loots.end();)
    {   
        glm::vec2 vectorDirection = glm::vec2(playerPos.x - it->position.x, playerPos.y - it->position.y);
        float distance = sqrt(pow(vectorDirection.x, 2) + pow(vectorDirection.y, 2));
        if (distance < PLAYER_LOOT_RADIUS)
        {
            glm::vec2 vectorDirectionNormalized = vectorDirection;
            if (vectorDirectionNormalized != glm::vec2(0, 0))
                vectorDirectionNormalized = glm::normalize(vectorDirectionNormalized);
            it->position = it->position + vectorDirectionNormalized * LOOT_SPEED; // maybe do a thing to accelerate over time
        }

        if (distance < PLAYER_CLOSE_LOOT_RADIUS)
        {
            // @todo add to inventory
            it = loots.erase(it);
            continue;
        }

        SpriteRenderer::Draw(it->position, glm::vec2(SPRITE_SIZE, SPRITE_SIZE), 0, glm::vec3(1, 1, 1), it->sprite, false, false, 1);
        it++;
    }
}