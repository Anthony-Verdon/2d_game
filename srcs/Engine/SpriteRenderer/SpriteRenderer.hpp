#pragma once

#include <glm/glm.hpp>
#include <string>
#include "Engine/SpriteData/SpriteData.hpp"

class SpriteRenderer: public SpriteData
{
    private:
        unsigned int VAO;
        unsigned int VBO;
        bool isInit;

    public: 
        SpriteRenderer();
        SpriteRenderer(const std::string &texture, const glm::vec2 &textureSize, const glm::vec2 &spriteCoords, const glm::vec2 &size, float rotation, const glm::vec3 &color);
        ~SpriteRenderer();

        void Init(const glm::vec2 &textureSize, const glm::vec2 &spriteCoords);
        void Draw(float x, float y);
        void Draw(const glm::vec2 &position);
};