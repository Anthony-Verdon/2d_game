#pragma once

#include "Game/ItemBehavior/AItemBehavior/AItemBehavior.hpp"

class AxeBehavior: public AItemBehavior
{
    public:
        AxeBehavior();
        ~AxeBehavior();

        void MainAction(const glm::vec2 &actionCoords);
};