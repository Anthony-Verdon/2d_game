#pragma once

#include <glm/glm.hpp>
#include <string>
#include "Engine/ARenderer/ARenderer.hpp"

class SpriteRenderer: public ARenderer
{
    private:
        std::string texture;
        glm::vec2 size;
        void Init();
        
    public: 
        SpriteRenderer();
        SpriteRenderer(const std::string &texture, const glm::vec2 &size, const glm::vec2 &position, float rotation, const glm::vec3 &color);
        ~SpriteRenderer();

        void Draw();

        void SetTexture(const std::string &texture);
        void SetSize(const glm::vec2 &size);
        void SetSprite(const glm::vec2 &textureSize, const glm::vec2 &spriteCoords);
};