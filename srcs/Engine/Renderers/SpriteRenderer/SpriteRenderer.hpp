#pragma once

#include <glm/glm.hpp>
#include <string>
#include "Engine/Sprite/Sprite.hpp"

class SpriteRenderer
{
    private:
        static unsigned int VAO;
        static unsigned int VBO;
        static bool isInit;

        SpriteRenderer() = delete;
        ~SpriteRenderer() = delete;
        
    public: 
        static void Init();
        static void Destroy();
        static void Draw(const glm::vec2 &position, const glm::vec2 &size, float rotation, const glm::vec3 &color, const Sprite &sprite, bool flipHorizontally, bool flipVertically, float opacity);
};