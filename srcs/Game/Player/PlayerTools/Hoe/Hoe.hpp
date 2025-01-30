#pragma once

#include "Game/Player/PlayerTools/APlayerTool/APlayerTool.hpp"

class Hoe: public APlayerTool
{
    public:
        Hoe();
        ~Hoe();

        void MainAction(const glm::vec2 &actionCoords);
};