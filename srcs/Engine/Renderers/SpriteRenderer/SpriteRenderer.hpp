#pragma once

#include <glm/glm.hpp>
#include <string>
#include "Engine/Sprite/Sprite.hpp"

struct SpriteRenderData
{
    glm::vec2 position;
    glm::vec2 size;
    float rotation;
    glm::vec3 color;
    Sprite sprite;
    bool flipHorizontally;
    bool flipVertically;
    float opacity;
    bool drawAbsolute;

    SpriteRenderData()
    {
        position = glm::vec2(0, 0);
        size = glm::vec2(0, 0);
        rotation = 0;
        color = glm::vec3(1, 1, 1);
        sprite = Sprite::none;
        flipHorizontally = false;
        flipVertically = false;
        opacity = 1;
        drawAbsolute = false;
    }
};

class SpriteRenderer
{
    private:
        static unsigned int VAO;
        static unsigned int VBO;
        static bool isInit;

        static glm::mat4 projectionMatAbsolute;
        static glm::mat4 projectionMatRelative;
        
        SpriteRenderer() = delete;
        ~SpriteRenderer() = delete;
        
    public: 
        static void Init();
        static void Destroy();
        static void Draw(const SpriteRenderData &data);
        static void Draw(const glm::vec2 &position, const glm::vec2 &size, float rotation, const glm::vec3 &color, const Sprite &sprite, bool flipHorizontally, bool flipVertically, float opacity, bool drawAbsolute = false);

        static void SetProjectionMatRelative(const glm::mat4 &projectionMatRelative) { SpriteRenderer::projectionMatRelative = projectionMatRelative; }
};