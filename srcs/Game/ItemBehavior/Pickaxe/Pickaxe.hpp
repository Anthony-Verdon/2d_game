#pragma once

#include "Game/ItemBehavior/AItemBehavior/AItemBehavior.hpp"

class Pickaxe: public AItemBehavior
{
    public:
        Pickaxe();
        ~Pickaxe();

        void MainAction(const glm::vec2 &actionCoords);
};