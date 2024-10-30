#pragma once

#include <glm/glm.hpp>
#include <string>
#include "Engine/SpriteData/SpriteData.hpp"
#include "Engine/GameObject/GameObject.hpp"

class SpriteRenderer: public GameObject, public SpriteData
{
    private:
        unsigned int VAO;
        unsigned int VBO;

        void Init();
        
    public: 
        SpriteRenderer();
        SpriteRenderer(const std::string &texture, const glm::vec2 &size, float rotation, const glm::vec3 &color);
        ~SpriteRenderer();

        void Draw(const glm::vec2 &position, const glm::vec2 &textureSize, const glm::vec2 &spriteCoords);
};