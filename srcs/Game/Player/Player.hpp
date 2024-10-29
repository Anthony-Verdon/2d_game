#pragma once

#include "Engine/SpriteRenderer/SpriteRenderer.hpp"
#include "Engine/SquareHitbox/SquareHitbox.hpp"

class Player: public SpriteRenderer
{
    private:
        glm::vec2 coords;
        float speed;
        SquareHitbox hitbox;

    public:
        Player();
        ~Player();

    glm::vec2 GetCoords() const;
    void Move(const glm::vec2 &direction);
};