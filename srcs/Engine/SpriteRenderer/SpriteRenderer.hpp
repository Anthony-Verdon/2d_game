#pragma once

#include <glm/glm.hpp>
#include <string>

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
        static void Draw(const glm::vec2 &position, const glm::vec2 &size, float rotation, const glm::vec3 &color, const std::string &texture, const glm::vec2 &textureSize, const glm::vec2 &spriteCoords);
};