#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include "Engine/Tile/Tile.hpp"
#include "Editor/ToolSelector/ATool.hpp"


struct TextureData
{
    std::string name;
    std::string path;
    glm::vec2 nbSprite;
    glm::vec2 spriteOffset;
};

class TileSelector: public ATool
{
    private:
        std::vector<TextureData> texturesData;
        Tile tileSelected;

        void InputFields();
        void TilesAdded();
    
    public:
        TileSelector();
        ~TileSelector();

        void Draw();

        void Load();
        void Save();

        Tile GetTile() const;
};