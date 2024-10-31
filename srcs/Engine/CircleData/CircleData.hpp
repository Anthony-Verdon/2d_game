#pragma once

#include <glm/glm.hpp>

class CircleData
{
    protected:
        float radius;
        glm::vec2 center;
        glm::vec3 color;

    public:
        CircleData();
        CircleData(float radius, const glm::vec2 &center, const glm::vec3 &color);
        ~CircleData();

        void SetRadius(float radius);
        void SetCenter(const glm::vec2 &center);
        void SetColor(const glm::vec3 &color);

        float GetRadius() const;
        glm::vec2 GetCenter() const;
        glm::vec3 GetColor() const;
};