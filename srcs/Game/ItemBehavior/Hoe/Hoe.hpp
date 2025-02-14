#pragma once

#include "Game/ItemBehavior/AItemBehavior/AItemBehavior.hpp"

class Hoe: public AItemBehavior
{
    public:
        Hoe();
        ~Hoe();

        void MainAction(const glm::vec2 &actionCoords);
};