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

    public:
        SpriteData();
        SpriteData(const std::string &texture, const glm::vec2 &size, float rotation);
        virtual ~SpriteData();

        void SetTexture(const std::string &texture);
        void SetSize(const glm::vec2 &size);
        void SetRotation(float rotation);
};