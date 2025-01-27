#pragma once

#include <glm/glm.hpp>

enum PlayerTool
{
    SWORD,
    PICKAXE,
    AXE
};

class APlayerTool
{
    protected:
        PlayerTool toolType;

    public:
        APlayerTool() {}
        virtual ~APlayerTool() {}

        virtual void MainAction(const glm::vec2 &actionCoords) { (void)actionCoords; }

        PlayerTool GetType() {return toolType; }
};