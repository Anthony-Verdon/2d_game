#pragma once

#include <glm/glm.hpp>
#include "Engine/GameObject/GameObject.hpp"

class ARenderer: public GameObject
{
    protected:
        unsigned int VAO;
        unsigned int VBO;
        unsigned int EBO;
        glm::vec3 color;

        virtual void Init() = 0;
    public:
        ARenderer();
        ARenderer(const glm::vec3 &color, const glm::vec2 &position, float rotation);
        virtual ~ARenderer();

        virtual void Draw() = 0;
        void SetColor(const glm::vec3 &color);
        glm::vec3 GetColor() const;
        
        
};