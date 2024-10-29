#pragma once

#include <glm/glm.hpp>

class SquareHitbox
{
    private:
        glm::vec2 coords;
        glm::vec2 size;

    public:
        SquareHitbox();
        SquareHitbox(const glm::vec2 &coords, const glm::vec2 &size);
        ~SquareHitbox();

        bool IsColliding(const SquareHitbox &instance) const;

        glm::vec2 GetCoords() const;
        float GetX() const;
        float GetY() const;

        glm::vec2 GetSize() const;
        float GetWidth() const;
        float GetHeight() const;

        void Draw() const;
};