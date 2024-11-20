#pragma once

#include <glm/glm.hpp>
#include <vector>

class CircleRenderer
{
     private:
        static unsigned int VAO;
        static unsigned int nbTriangles;
        static bool isInit;
        static std::vector<float> vertices;

        CircleRenderer() = delete;
        ~CircleRenderer() = delete;
    public: 
        static void Init();
        static void Destroy();
        static void Draw(const glm::vec2 &position, float radius, float rotation, const glm::vec3 &fillColor, const glm::vec3 &edgeColor = glm::vec3(0, 0, 0));
        static void Draw(const glm::vec2 &position, float radius, float rotation, const glm::vec4 &fillColor, const glm::vec4 &edgeColor = glm::vec4(0, 0, 0, 0));
};