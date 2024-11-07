#pragma once

#include <glm/glm.hpp>

class CircleRenderer
{
     private:
        static unsigned int VAO;
        static unsigned int nbTriangles;
        static bool isInit;

        CircleRenderer() = delete;
        ~CircleRenderer() = delete;
    public: 
        static void Init(unsigned int width, unsigned int height);
        static void Destroy();
        static void Draw(const glm::vec2 &position, float radius, float rotation, const glm::vec3 &color);
};