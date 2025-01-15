#pragma once

#include "Engine/TilemapManager/TilemapManager.hpp"
#include "Editor/AEditorWindow/AEditorWindow.hpp"
#include "globals.hpp"

class TilemapManagerUI: public AEditorWindow
{
    private:
        TilemapManager tilemapManager;
        std::string tilemapSelected;
        char name[INPUT_ARRAY_SIZE];

    public:
        TilemapManagerUI();
        ~TilemapManagerUI();

        void Draw();

        void AddTile(const glm::vec2 &position, const Tile &tile);
        void AddTile(const glm::vec2 &position, const Sprite &sprite);
        void SuppressTile(const glm::vec2 &position);
};