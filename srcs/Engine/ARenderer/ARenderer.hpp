#pragma once

#include <glm/glm.hpp>

class ARenderer
{
    protected:
        unsigned int VAO;
        unsigned int VBO;
        glm::vec3 color;

        virtual void Init() = 0;
    public:
        ARenderer();
        ARenderer(const glm::vec3 &color);
        virtual ~ARenderer();

        virtual void CalculateMesh() = 0;
        virtual void Draw() = 0;

        void SetColor(const glm::vec3 &color);
        glm::vec3 GetColor() const;
};