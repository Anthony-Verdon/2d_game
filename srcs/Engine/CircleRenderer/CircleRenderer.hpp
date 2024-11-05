#pragma once

#include "Engine/ARenderer/ARenderer.hpp"

class CircleRenderer: public ARenderer
{
     private:
        unsigned int numTriangles;
        float radius;

        void Init();
        
        void SetNumTriangles(unsigned int numTriangles);
        unsigned int GetNumTriangles() const;
        
    public: 
        CircleRenderer();
        CircleRenderer(const glm::vec2 &position, float radius, const glm::vec3 &color, unsigned int numTriangles, float rotation, float mass, float restitution);
        ~CircleRenderer();

        void Draw();

        
        void SetRadius(float radius);
        float GetRadius() const;
};