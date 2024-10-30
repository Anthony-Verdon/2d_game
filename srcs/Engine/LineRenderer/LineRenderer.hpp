#pragma once

#include "Engine/LineData/LineData.hpp"

class LineRenderer: public LineData
{
    private:
        unsigned int VAO;
        unsigned int VBO;

        void Init();
    public: 
        LineRenderer();
        LineRenderer(const glm::vec2 &start, const glm::vec2 &end,const glm::vec3 &color);
        ~LineRenderer();

        void Draw();
};