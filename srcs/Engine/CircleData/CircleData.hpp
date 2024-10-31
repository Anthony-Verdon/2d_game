#pragma once

#include <glm/glm.hpp>

class CircleData
{
    protected:
        float radius;
        glm::vec2 center;

    public:
        CircleData();
        CircleData(float radius, const glm::vec2 &center);
        ~CircleData();

        void SetRadius(float radius);
        void SetCenter(const glm::vec2 &center);

        float GetRadius() const;
        glm::vec2 GetCenter() const;
};