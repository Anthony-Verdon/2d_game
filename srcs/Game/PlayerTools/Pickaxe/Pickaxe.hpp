#pragma once

#include "Game/PlayerTools/APlayerTool/APlayerTool.hpp"

class Pickaxe: public APlayerTool
{
    public:
        Pickaxe();
        ~Pickaxe();

        void MainAction(const glm::vec2 &actionCoords);
};