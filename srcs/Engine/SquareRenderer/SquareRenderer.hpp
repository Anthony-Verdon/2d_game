#pragma once

#include "Engine/SquareData/SquareData.hpp"
#include "Engine/ARenderer/ARenderer.hpp"

class SquareRenderer: public SquareData, public ARenderer
{
    private:
        void Init();

    public:
        SquareRenderer();
        SquareRenderer(const glm::vec2 &coords, const glm::vec2 &size, const glm::vec3 &color);
        ~SquareRenderer();

        void CalculateMesh();
        void Draw();
};