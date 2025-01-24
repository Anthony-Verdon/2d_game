#pragma once

#include <glm/glm.hpp>

enum PlayerTool
{
    SWORD,
    PICKAXE,
};

class APlayerTool
{
    protected:
        PlayerTool toolType;

    public:
        APlayerTool() {}
        virtual ~APlayerTool() {}

        virtual void MainAction(const glm::vec2 &actionCoords) = 0;

        PlayerTool GetType() {return toolType; }
};