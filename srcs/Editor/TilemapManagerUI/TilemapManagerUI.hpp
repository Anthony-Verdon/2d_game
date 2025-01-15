#pragma once

#include "Engine/TilemapManager/TilemapManager.hpp"
#include "Editor/AEditorWindow/AEditorWindow.hpp"

class TilemapManagerUI: public AEditorWindow
{
    private:
        TilemapManager tilemapManager;
    public:
        TilemapManagerUI();
        ~TilemapManagerUI();

        void Draw();
};