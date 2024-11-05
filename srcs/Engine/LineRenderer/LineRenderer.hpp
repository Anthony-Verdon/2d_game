#pragma once

#include "Engine/LineData/LineData.hpp"
#include "Engine/ARenderer/ARenderer.hpp"

class LineRenderer: public LineData, public ARenderer
{
    private:
        void Init();
        
    public: 
        LineRenderer();
        LineRenderer(const glm::vec2 &start, const glm::vec2 &end, const glm::vec2 &position, float rotation, const glm::vec3 &color);
        ~LineRenderer();

        void CalculateMesh();
        void Draw();
};