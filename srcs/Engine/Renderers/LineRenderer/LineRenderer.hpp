#pragma once

#include <glm/glm.hpp>

class LineRenderer
{
    private:
        static unsigned int VAO;
        static unsigned int VBO;
        static bool isInit;

        LineRenderer() = delete;
        ~LineRenderer() = delete;
    public: 
        static void Init(unsigned int width, unsigned int height);
        static void Destroy();
        static void Draw(const glm::vec2 &va, const glm::vec2 &vb, const glm::vec3 &color);
};