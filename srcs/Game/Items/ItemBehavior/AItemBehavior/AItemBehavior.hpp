#pragma once

#include <glm/glm.hpp>

class AItemBehavior
{
    public:
    AItemBehavior() {}
        virtual ~AItemBehavior() {}

        virtual void MainAction(const glm::vec2 &actionCoords = glm::vec2(0, 0)) { (void)actionCoords; }
};