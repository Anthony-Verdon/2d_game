#pragma once

#include "Engine/TilemapManager/TilemapManager.hpp"
#include "Editor/AEditorWindow/AEditorWindow.hpp"
#include "globals.hpp"

class TilemapManagerUI: public AEditorWindow
{
    private:
        std::string tilemapSelected;
        char name[INPUT_ARRAY_SIZE];

    public:
        TilemapManagerUI();
        ~TilemapManagerUI();

        void Draw();

        void AddTile(const glm::vec2 &position, const Tile &tile);
        void AddTile(const glm::vec2 &position, const Sprite &sprite, const glm::vec2 &spriteOffset);
        void SuppressTile(const glm::vec2 &position);

        void Load();
        void Save();
};