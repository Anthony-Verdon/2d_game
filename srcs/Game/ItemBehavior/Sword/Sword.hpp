#pragma once

#include "Game/ItemBehavior/AItemBehavior/AItemBehavior.hpp"

class Sword: public AItemBehavior
{
    public:
        Sword();
        ~Sword();

        void MainAction(const glm::vec2 &actionCoords);
};