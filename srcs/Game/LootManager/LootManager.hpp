#pragma once

#include "Game/LootManager/Loot.hpp"
#include <vector>

class LootManager
{
    private:
        static std::vector<Loot> loots;

        LootManager() = delete;
        ~LootManager() = delete;

    public:
        static void AddLoot(const Loot &loot);

        static void Update(const glm::vec2 &playerPos);
        static void Draw();
};