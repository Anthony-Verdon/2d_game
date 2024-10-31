#pragma once

#include <glm/glm.hpp>
#include <string>
#include "Engine/SpriteData/SpriteData.hpp"
#include "Engine/GameObject/GameObject.hpp"
#include "Engine/ARenderer/ARenderer.hpp"

class SpriteRenderer: public GameObject, public SpriteData, public ARenderer
{
    private:
        void Init();
        
        void CalculateMesh();
        void Draw();
    public: 
        SpriteRenderer();
        SpriteRenderer(const std::string &texture, const glm::vec2 &size, float rotation, const glm::vec3 &color);
        ~SpriteRenderer();

        void CalculateMesh(const glm::vec2 &textureSize, const glm::vec2 &spriteCoords);
        void Draw(const glm::vec2 &position);
};