#pragma once

#include "Engine/SquareData/SquareData.hpp"

class SquareRenderer: public SquareData
{
    private:
        unsigned int VAO;
        unsigned int VBO;

        void Init();

    public:
        SquareRenderer();
        SquareRenderer(const glm::vec2 &coords, const glm::vec2 &size, const glm::vec3 &color);
        ~SquareRenderer();

        void CalculateMesh();
        void Draw();
};