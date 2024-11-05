#pragma once

#include "Engine/ARenderer/ARenderer.hpp"
#include <vector>

#define SQUARE_VERTICES std::vector<float> {    \
        0, 0,                                   \
        1, 0,                                   \
        1, 1,                                   \
        0, 1                                    \
}

#define SQUARE_FACES std::vector<int>{  \
       3, 1, 0,                         \
       3, 2, 1                          \
}                                           

#define PENTAGON_VERTICES std::vector<float> {  \
        0.5,  0,                                \
        1,    0.5,                              \
        0.75, 1,                                \
        0.25, 1,                                \
        0,    0.5,                              \
}

#define PENTAGON_FACES std::vector<int>{      \
       3, 0, 4,                               \
       3, 1, 0,                               \
       3, 2, 1                                \
}   

class PolygonRenderer: public ARenderer
{
    private:
        void Init();
        glm::vec2 size;
        std::vector<float> vertices;
        std::vector<int> faces;

        glm::mat4 CalculateModelMatrix() const;

    public:
        PolygonRenderer();
        PolygonRenderer(const std::vector<float> &vertices, const std::vector<int> &faces,const glm::vec2 &position, float rotation, const glm::vec2 &size, const glm::vec3 &color, float mass, float restitution);
        ~PolygonRenderer();

        void Draw();
        std::vector<glm::vec2> CalculateVerticesPosition() const;

        void SetSize(const glm::vec2 &size);
        glm::vec2 GetSize() const;
        float GetWidth() const;
        float GetHeight() const;
};