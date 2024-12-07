#pragma once

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

        virtual void MainAction() = 0;

        PlayerTool GetType() {return toolType; }
};