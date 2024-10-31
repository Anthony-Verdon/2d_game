#pragma once

#include <glm/glm.hpp>

class SquareData
{
    protected:
        glm::vec2 coords;
        glm::vec2 size;
        glm::vec3 color;

    public:
        SquareData();
        SquareData(const glm::vec2 &coords, const glm::vec2 &size, const glm::vec3 &color);
        ~SquareData();

        void SetCoords(const glm::vec2 &coords);
        glm::vec2 GetCoords() const;
        float GetX() const;
        float GetY() const;

        void SetSize(const glm::vec2 &size);
        glm::vec2 GetSize() const;
        float GetWidth() const;
        float GetHeight() const;

        void SetColor(const glm::vec3 &color);
        glm::vec3 GetColor() const;
};