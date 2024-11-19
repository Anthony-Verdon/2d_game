#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include "Engine/Renderers/SpriteRenderer/SpriteRenderer.hpp"

struct TextureData
{
    std::string name;
    glm::vec2 size;
};

class TileSelector
{
    private:
        // input data
        char name[100];
        char path[100];
        glm::vec2 nbSprite;

        bool isHoveredOrFocused;

        std::vector<TextureData> texturesData;
        Sprite tileSelected;

        void InputFields();
        void TilesAdded();
    
    public:
        TileSelector();
        ~TileSelector();

        void Draw();

        Sprite GetTile() const;
        bool IsHoveredOrFocused() const;
};