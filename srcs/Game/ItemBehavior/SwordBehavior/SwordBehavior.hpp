#pragma once

#include "Game/ItemBehavior/AItemBehavior/AItemBehavior.hpp"

class SwordBehavior: public AItemBehavior
{
    public:
        SwordBehavior();
        ~SwordBehavior();

        void MainAction(const glm::vec2 &actionCoords);
};