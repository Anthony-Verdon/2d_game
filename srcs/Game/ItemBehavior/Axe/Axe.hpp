#pragma once

#include "Game/ItemBehavior/AItemBehavior/AItemBehavior.hpp"

class Axe: public AItemBehavior
{
    public:
        Axe();
        ~Axe();

        void MainAction(const glm::vec2 &actionCoords);
};