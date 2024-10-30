#pragma once

#include <glm/glm.hpp>
#include "Engine/LineRenderer/LineRenderer.hpp"
#include "Engine/GameObject/GameObject.hpp"

class SquareHitbox: public GameObject
{
    private:
        glm::vec2 coords;
        glm::vec2 size;
        LineRenderer lineRenderer;

    public:
        SquareHitbox();
        SquareHitbox(const glm::vec2 &coords, const glm::vec2 &size);
        ~SquareHitbox();

        bool IsColliding(const SquareHitbox &instance) const;

        void SetCoords(const glm::vec2 &coords);
        glm::vec2 GetCoords() const;
        float GetX() const;
        float GetY() const;

        void SetSize(const glm::vec2 &size);
        glm::vec2 GetSize() const;
        float GetWidth() const;
        float GetHeight() const;

        void Draw();
};