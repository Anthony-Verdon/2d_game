#pragma once

#include "Engine/GameObject/GameObject.hpp"
#include "Engine/CircleData/CircleData.hpp"

class CircleRenderer: public GameObject, public CircleData
{
     private:
        unsigned int VAO;
        unsigned int VBO;

        unsigned int numTriangles;

        void Init();
        
    public: 
        CircleRenderer();
        CircleRenderer(float radius, const glm::vec2 &center, const glm::vec3 &color, unsigned int numTriangles);
        ~CircleRenderer();

        void CalculateMesh();
        void Draw();

        void SetNumTriangles(unsigned int numTriangles);
        unsigned int GetNumTriangles() const;
};