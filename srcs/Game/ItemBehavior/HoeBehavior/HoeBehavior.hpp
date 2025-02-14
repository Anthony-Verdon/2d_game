#pragma once

#include "Game/ItemBehavior/AItemBehavior/AItemBehavior.hpp"

class HoeBehavior: public AItemBehavior
{
    public:
        HoeBehavior();
        ~HoeBehavior();

        void MainAction(const glm::vec2 &actionCoords);
};