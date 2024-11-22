#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include "Engine/Renderers/SpriteRenderer/SpriteRenderer.hpp"
#include "Editor/ToolSelector/ToolSelector.hpp"

constexpr int arraySize = 100;

struct TextureData
{
    std::string name;
    std::string path;
    glm::vec2 nbSprite;
    float spriteScale;
};

class TileSelector: public ATool
{
    private:
        // input data
        char name[arraySize];
        char path[arraySize];
        glm::vec2 nbSprite;

        std::vector<TextureData> texturesData;
        Sprite tileSelected;

        void InputFields();
        void TilesAdded();
    
    public:
        TileSelector();
        ~TileSelector();

        void Draw();

        void Load();
        void Save();

        Sprite GetTile() const;
};