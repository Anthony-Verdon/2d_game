#pragma once

#include "Engine/ARenderer/ARenderer.hpp"
#include "Engine/Transform/Transform.hpp"

class SquareRenderer: public Transform, public ARenderer
{
    private:
        void Init();
        glm::vec2 size;

    public:
        SquareRenderer();
        SquareRenderer(const glm::vec2 &position, float rotation, const glm::vec2 &size, const glm::vec3 &color);
        ~SquareRenderer();

        void CalculateMesh();
        void Draw();

        void SetSize(const glm::vec2 &size);
        glm::vec2 GetSize() const;
        float GetWidth() const;
        float GetHeight() const;
};