#pragma once

#include "Engine/SpriteRenderer/SpriteRenderer.hpp"
#include "Engine/SquareHitbox/SquareHitbox.hpp"
#include "Engine/GameObject/GameObject.hpp"

class Player: public GameObject
{
    private:
        glm::vec2 coords;
        float speed;

    public:
        Player();
        ~Player();

        glm::vec2 GetCoords() const;
        const SquareHitbox &GetHitbox() const;

        void Move(const glm::vec2 &direction);
        void Draw();
};