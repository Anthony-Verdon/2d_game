#pragma once

#include "Engine/ARenderer/ARenderer.hpp"
#include <vector>

#define SQUARE_VERTICES std::vector<float> {    \
        -0.5, -0.5,                             \
         0.5, -0.5,                             \
         0.5,  0.5,                             \
        -0.5,  0.5                              \
}

#define SQUARE_FACES std::vector<int>{  \
       3, 1, 0,                         \
       3, 2, 1                          \
}                                           

#define PENTAGON_VERTICES std::vector<float> {  \
            0, -0.5,                            \
          0.5,    0,                            \
         0.25,  0.5,                            \
        -0.25,  0.5,                            \
         -0.5,    0,                            \
}

#define PENTAGON_FACES std::vector<int>{      \
       3, 0, 4,                               \
       3, 1, 0,                               \
       3, 2, 1                                \
}   

class PolygonBody: public ARenderer
{
    private:
        void Init();
        glm::vec2 size;
        std::vector<float> vertices;
        std::vector<int> faces;

        glm::mat4 CalculateModelMatrix() const;

    public:
        PolygonBody();
        PolygonBody(const std::vector<float> &vertices, const std::vector<int> &faces,const glm::vec2 &position, float rotation, const glm::vec2 &size, const glm::vec3 &color, float mass, float restitution, bool isStatic);
        ~PolygonBody();

        void Draw();
        std::vector<glm::vec2> CalculateVerticesPosition() const;

        void SetSize(const glm::vec2 &size);
        glm::vec2 GetSize() const;
        float GetWidth() const;
        float GetHeight() const;

        void CalculateInertia();
        glm::vec2 GetPosition() const;
};