#pragma once

#include "Engine/GameObject/GameObject.hpp"
#include "Engine/Transform/Transform.hpp"
#include "Engine/ARenderer/ARenderer.hpp"

class CircleRenderer: public GameObject, public Transform, public ARenderer
{
     private:
        unsigned int numTriangles;
        float radius;

        void Init();
        
    public: 
        CircleRenderer();
        CircleRenderer(const glm::vec2 &position, float radius, const glm::vec3 &color, unsigned int numTriangles, float rotation);
        ~CircleRenderer();

        void CalculateMesh();
        void Draw();

        void SetNumTriangles(unsigned int numTriangles);
        unsigned int GetNumTriangles() const;
        
        void SetRadius(float radius);
       float GetRadius() const;
};