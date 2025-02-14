#pragma once

#include <glm/glm.hpp>

enum PlayerTool
{
    SWORD,
    PICKAXE,
    AXE,
    HOE,
    WATERING_CAN
};

class AItemBehavior
{
    protected:
        PlayerTool toolType;

    public:
    AItemBehavior() {}
        virtual ~AItemBehavior() {}

        virtual void MainAction(const glm::vec2 &actionCoords = glm::vec2(0, 0)) { (void)actionCoords; }

        PlayerTool GetType() {return toolType; }
};