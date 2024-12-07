#pragma once

#include "Game/PlayerTools/APlayerTool/APlayerTool.hpp"

class Sword: public APlayerTool
{
    public:
        Sword();
        ~Sword();

        void MainAction();
};