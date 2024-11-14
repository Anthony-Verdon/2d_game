#pragma once

#include <glm/glm.hpp>
#include <string>

struct Sprite
{
    std::string textureName;
    glm::vec2 textureSize; // nb sprite on x and y axis
    glm::vec2 spriteCoords; // depending of texture size
};

class SpriteRenderer
{
    private:
        static unsigned int VAO;
        static unsigned int VBO;
        static bool isInit;

        SpriteRenderer() = delete;
        ~SpriteRenderer() = delete;
        
    public: 
        static void Init(unsigned int width, unsigned int height);
        static void Destroy();
        static void Draw(const glm::vec2 &position, const glm::vec2 &size, float rotation, const glm::vec3 &color, const Sprite &sprite, bool flipHorizontally, bool flipVertically);
};