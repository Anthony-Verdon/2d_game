#pragma once

#include <glm/glm.hpp>
#include <string>
#include "Engine/Texture/Texture.hpp"

class SpriteData
{
    protected:
        std::string texture;
        glm::vec2 size;
        float rotation;
        glm::vec3 color;

    public:
        SpriteData();
        SpriteData(const std::string &texture, const glm::vec2 &size, float rotation, const glm::vec3 &color);
        virtual ~SpriteData();

        void SetTexture(const std::string &texture);
        void SetSize(const glm::vec2 &size);
        void SetRotation(float rotation);
        void SetColor(const glm::vec3 &color);
};