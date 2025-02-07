#pragma once

#include "Game/Player/PlayerTools/APlayerTool/APlayerTool.hpp"

class Axe: public APlayerTool
{
    public:
        Axe();
        ~Axe();

        void MainAction(const glm::vec2 &actionCoords);
};