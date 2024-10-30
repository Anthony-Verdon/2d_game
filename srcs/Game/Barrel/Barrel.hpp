#pragma once

#include "Engine/SpriteRenderer/SpriteRenderer.hpp"
#include "Engine/SquareHitbox/SquareHitbox.hpp"

class Barrel
{
    private:
        glm::vec2 coords;
        SpriteRenderer spriteRenderer;
        SquareHitbox hitbox;

    public:
        Barrel();
        ~Barrel();
        
        const SquareHitbox &GetHitbox() const;

        void Draw();
};