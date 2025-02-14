#pragma once

#include "Game/ItemBehavior/AItemBehavior/AItemBehavior.hpp"

class PickaxeBehavior: public AItemBehavior
{
    public:
        PickaxeBehavior();
        ~PickaxeBehavior();

        void MainAction(const glm::vec2 &actionCoords);
};