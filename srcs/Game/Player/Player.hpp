#pragma once

#include "Engine/SpriteRenderer/SpriteRenderer.hpp"
#include "Engine/SquareHitbox/SquareHitbox.hpp"

class Player
{
    private:
        glm::vec2 coords;
        float speed;
        SpriteRenderer spriteRenderer;
        SquareHitbox hitbox;

    public:
        Player();
        ~Player();

        glm::vec2 GetCoords() const;
        void Move(const glm::vec2 &direction);
        void Draw();
};